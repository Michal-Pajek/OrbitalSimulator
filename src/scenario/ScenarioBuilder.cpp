#include "scenario/ScenarioBuilder.hpp"
#include <stdexcept>
#include <utility>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/DataGetter.hpp"
#include "input/Keyboard.hpp"
#include "physics/Constants.hpp"
#include "simulation/bodies/Body.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	enum class Decision {
		Accept,
		Revise,
		Cancel
	};

	enum class PartToChange {
		TimeStep,
		StepCount,
		ScenarioName,
		Bodies,
		Cancel
	};

	struct MenuOptionPair {
		TextId textId;
		double multiplier;
		MenuOptionPair() = delete;
		MenuOptionPair(TextId _textId, double _multiplier) : textId{ _textId }, multiplier{ _multiplier } {}
	};

	double getUnitMultiplier(const std::vector<MenuOptionPair>& options, const TextId menuTitle)
	{
		const auto size{ options.size() };
		if (size == 0 || size >= 10u) {
			throw std::invalid_argument("Options vector in getUnitMultiplier must be between 1 and 9");
		}

		double result{};
		TextId selectedUnit;
		auto key{ '1' };
		std::vector<MenuOption> menuOptions{};
		menuOptions.reserve(size);
		for (size_t idx{}; idx < size; ++idx) {
			const auto& multiplier{ options.at(idx).multiplier };
			const auto& textId{ options.at(idx).textId };
			menuOptions.emplace_back(key++, textId, [&result, &selectedUnit, multiplier, textId]() {result = multiplier; selectedUnit = textId; });
		}

		const Menu selectUnitMenu{ menuOptions, menuTitle };
		selectUnitMenu.execute();
		ConsoleWriter::writeLine(TextId::SelectedUnit, ": ", selectedUnit);
		return result;
	}

	Decision getScenarioAcceptanceDecision()
	{
		Decision result;
		const Menu scenarioAcceptanceMenu{ {
			MenuOption{'A', TextId::Accept,	[&result]() {result = Decision::Accept; }},
			MenuOption{'R', TextId::Revise,	[&result]() {result = Decision::Revise; }},
			MenuOption{'C', TextId::Cancel,	[&result]() {result = Decision::Cancel; }}},
			TextId::QuestionWhatDoYouWantToDo };
		scenarioAcceptanceMenu.execute();
		return result;
	}

	PartToChange getWhatToChangeDecision()
	{
		PartToChange result;
		const Menu whatToChangeMenu{ {
			MenuOption{'T', TextId::TimeStep,		[&result]() {result = PartToChange::TimeStep; }},
			MenuOption{'S', TextId::StepCount,		[&result]() {result = PartToChange::StepCount; }},
			MenuOption{'N',	TextId::ScenarioName,	[&result]() {result = PartToChange::ScenarioName; }},
			MenuOption{'B', TextId::Bodies,			[&result]() {result = PartToChange::Bodies; }},
			MenuOption{'C', TextId::Cancel,			[&result]() {result = PartToChange::Cancel; }}},
			TextId::QuestionWhatDoYouWantToChange };
		whatToChangeMenu.execute();
		return result;
	}
} // anonymous namespace

std::optional<Scenario> ScenarioBuilder::buildScenario()
{
	resetState();
	promptForScenarioName();
	promptForTimeStep();
	promptForStepCount();
	createBodiesFromInput();
	if (reviewAndConfirmScenario()) {
		return Scenario{ m_timeStep, m_stepCount, std::move(m_name), std::move(m_bodies) };
	}
	return std::nullopt;
}

bool ScenarioBuilder::isBodyNameAlreadyUsed(const std::string& checkedName) const
{
	return doesAnyBodyMatch([&checkedName](const Body& body) {return body.getName() == checkedName; });
}

bool ScenarioBuilder::isBodyPositionAlreadyUsed(const Vector3D& position) const
{
	return doesAnyBodyMatch([&position](const Body& body) {return body.getPosition() == position; });
}

bool ScenarioBuilder::reviewAndConfirmScenario()
{
	while (true) {
		printScenarioSummary();

		const auto decision{ getScenarioAcceptanceDecision() };
		switch (decision) {
		case Decision::Accept:
			if (m_bodies.empty()) {
				throw std::logic_error("Scenario must contain at least one body");
			}
			return true;
		case Decision::Revise:
			reviseScenario();
			break;
		case Decision::Cancel:
			return false;
		default:
			throw std::logic_error("Wrong decision selected");
		}
	}
}

double ScenarioBuilder::promptForBodyMass() const
{
	ConsoleWriter::writeLine();
	const auto massMultiplier{ getUnitMultiplier(std::vector<MenuOptionPair>{
		{TextId::Kilogram,	1.0},
		{TextId::Ton,		physics::TON},
		{TextId::Kiloton,	physics::KILOTON},
		{TextId::Megaton,	physics::MEGATON},
		{TextId::EarthMass, physics::EARTH_MASS},
		{TextId::SolarMass, physics::SOLAR_MASS}},
		TextId::SelectMassUnit) };
	ConsoleWriter::write(TextId::EnterBodyMass, ": ");

	return massMultiplier * DataGetter::getValue<double>([](const double x) {return x > 0.0; });
}

void ScenarioBuilder::createBodiesFromInput()
{
	constexpr auto MAX_BODYCOUNT{ 20 };
	m_bodies.clear();
	ConsoleWriter::writeLine();
	ConsoleWriter::write(TextId::EnterObjectCountNotGreaterThan, ' ', MAX_BODYCOUNT, ": ");
	const auto bodiesCount{ static_cast<unsigned int>(DataGetter::getValue<int>([](const int x) {return x > 0 && x <= MAX_BODYCOUNT; })) };
	m_bodies.reserve(bodiesCount);
	for (unsigned int i{}; i < bodiesCount; ++i) {
		m_bodies.emplace_back(createBodyFromInput());
	}

	clearScreen();
	reviewAndEditBodies();
}

void ScenarioBuilder::editBody(Body& body)
{
	clearScreen();
	ConsoleWriter::writeLine(TextId::YouAreEditingBody, ' ', body.getName());
	const Menu whatToChangeInBody{ {
			MenuOption{'N', TextId::BodyName,		[&body, this]() {body.setName(promptForBodyName(body.getName())); }},
			MenuOption{'M', TextId::BodyMass,		[&body, this]() {body.setMass(promptForBodyMass()); }},
			MenuOption{'P', TextId::BodyPosition,	[&body, this]() {body.setPosition(promptForBodyPosition(body.getPosition())); }},
			MenuOption{'V', TextId::BodyVelocity,	[&body, this]() {body.setVelocity(promptForBodyVelocity()); }},
			MenuOption{'B', TextId::Back,			[]() {}}},
			TextId::QuestionWhatDoYouWantToChangeInBody };
	whatToChangeInBody.execute();
}

void ScenarioBuilder::printBodies(const bool printHeadline) const
{
	if (printHeadline) {
		ConsoleWriter::writeHeadline(TextId::CurrentBodiesList);
	}
	ConsoleWriter::writeLine(TextId::ObjectCount, ":\t", m_bodies.size());
	auto counter{ 1 };

	for (const auto& body : m_bodies) {
		ConsoleWriter::write('\t', counter++, ":\t");
		body.printSummary(true);
	}
}

void ScenarioBuilder::printScenarioSummary() const
{
	clearScreen();
	ConsoleWriter::writeHeadline(TextId::CurrentScenarioSummary);
	ConsoleWriter::writeLine(TextId::ScenarioName, ":\t", m_name);
	ConsoleWriter::writeLine(TextId::TimeStep, ":\t", m_timeStep, 's');
	ConsoleWriter::writeLine(TextId::StepCount, ":\t", m_stepCount);
	ConsoleWriter::writeLine(TextId::Bodies, ':');
	printBodies(false);
}

void ScenarioBuilder::promptForScenarioName()
{
	ConsoleWriter::write(TextId::EnterScenarioName, ": ");
	m_name = DataGetter::getSingleWordText();
}

void ScenarioBuilder::promptForStepCount()
{
	ConsoleWriter::write('\n', TextId::EnterStepCount, ": ");
	m_stepCount = static_cast<unsigned int>(DataGetter::getValue<int>([](const int x) {return x > 0; }));
}

void ScenarioBuilder::promptForTimeStep()
{
	ConsoleWriter::writeLine();
	const auto timeMultiplier{ getUnitMultiplier(std::vector<MenuOptionPair>{
		{TextId::Second,	1.0},
		{TextId::Minute,	60.0},
		{TextId::Hour,		3600.0},
		{TextId::Day,		86400.0}},
		TextId::SelectTimeUnitForTimeStep) };
	ConsoleWriter::write(TextId::EnterTimeStep, " (", TextId::PositiveNumber, "): ");
	m_timeStep = timeMultiplier * DataGetter::getValue<double>([](const double x) { return x > 0.0; });
}

void ScenarioBuilder::resetState()
{
	m_bodies.clear();
	m_timeStep = {};
	m_name.clear();
	m_stepCount = {};
}

void ScenarioBuilder::reviewAndEditBodies()
{
	bool continueChecking{ true };
	while (continueChecking) {
		auto bodyCount{ static_cast<int>(m_bodies.size()) };

		if (bodyCount == 0) {
			ConsoleWriter::writeLine(TextId::ScenarioMustHaveAtLeastOneBody, ". ", TextId::PressAnyKeyToContinue);
			getSingleKey();
			m_bodies.emplace_back(createBodyFromInput());
			++bodyCount;
		}

		printBodies();

		const auto chooseBodyIdx{ [bodyCount]() {
			ConsoleWriter::write(TextId::EnterBodyNumber, ": ");
			return static_cast<size_t>(DataGetter::getValue<int>([bodyCount](const int value) {return 0 < value && value <= bodyCount; }) - 1);
			} };

		Menu whatToDoWithBodies{ {
			MenuOption{'A', TextId::Accept,		[&continueChecking]() {continueChecking = false; }},
			MenuOption{'B', TextId::AddBody,	[this]() {m_bodies.emplace_back(createBodyFromInput()); }},
			MenuOption{'D', TextId::DeleteBody,	[this, chooseBodyIdx]() {
				m_bodies.erase(m_bodies.begin() + chooseBodyIdx());
				ConsoleWriter::writeLine(TextId::BodyDeleted, '\n'); }},
			MenuOption{'E', TextId::EditBody,	[this, chooseBodyIdx]() {editBody(m_bodies.at(chooseBodyIdx())); }}},
			TextId::QuestionWhatDoYouWantToDoWithBodies };
		whatToDoWithBodies.execute();
	}
}

void ScenarioBuilder::reviewAndEditBody(Body& body)
{
	clearScreen();
	ConsoleWriter::writeHeadline(TextId::ConfirmBody);
	while (true) {
		body.printSummary();
		ConsoleWriter::writeLine();
		if (Menu::yesOrNo(TextId::QuestionDoYouWantToAccept)) {
			return;
		}

		editBody(body);
	}
}

void ScenarioBuilder::reviseScenario()
{
	const auto partToChange{ getWhatToChangeDecision() };

	switch (partToChange) {
	case PartToChange::TimeStep:
		promptForTimeStep();
		break;
	case PartToChange::StepCount:
		promptForStepCount();
		break;
	case PartToChange::ScenarioName:
		promptForScenarioName();
		break;
	case PartToChange::Bodies:
		reviewAndEditBodies();
		break;
	case PartToChange::Cancel:
		return;
	default:
		throw std::logic_error("Wrong decision selected");
	}
}

std::string ScenarioBuilder::promptForBodyName(const std::optional<std::string>& currentName) const
{
	ConsoleWriter::write(TextId::EnterOneWordName, ": ");
	auto enteredName{ DataGetter::getSingleWordText() };
	if (currentName && *currentName == enteredName) {
		return enteredName;
	}
	while (isBodyNameAlreadyUsed(enteredName)) {
		ConsoleWriter::write(TextId::BodyNameAlreadyUsedEnterAnother, ": ");
		enteredName = DataGetter::getSingleWordText();
	}
	return enteredName;
}

Body ScenarioBuilder::createBodyFromInput()
{
	clearScreen();
	ConsoleWriter::writeHeadline(TextId::EnterNewBodyData);
	const auto bodyName{ promptForBodyName() };
	const auto bodyMass{ promptForBodyMass() };
	const auto bodyPosition{ promptForBodyPosition() };
	const auto bodyVelocity{ promptForBodyVelocity() };

	Body result{ bodyName, {}, bodyMass, bodyPosition, bodyVelocity };		// temp

	reviewAndEditBody(result);

	return result;
}

Vector3D ScenarioBuilder::promptForBodyPosition(const std::optional<Vector3D>& currentPosition) const
{
	ConsoleWriter::writeLine();
	const auto distanceMultiplier{ getUnitMultiplier(std::vector<MenuOptionPair>{
		{TextId::Metre,							1.0},
		{TextId::Kilometre,						physics::KM_MULTIPLIER},
		{TextId::ThousandKilometre,				physics::KKM_MULTIPLIER},
		{TextId::MillionKilometre,				physics::MKM_MULTIPLIER},
		{TextId::AstronomicalUnit,				physics::AU},
		{TextId::AverageEarthToMoonDistance,	physics::EARTH_MOON_DISTANCE}},
		TextId::SelectDistanceUnit) };

	ConsoleWriter::write(TextId::EnterPositionVector, ": ");
	auto enteredPosition{ distanceMultiplier * DataGetter::getVector3D() };
	if (currentPosition && *currentPosition == enteredPosition) {
		return enteredPosition;
	}
	while (isBodyPositionAlreadyUsed(enteredPosition)) {
		ConsoleWriter::write(TextId::BodyPositionAlreadyOccupiedEnterAnother, ": ");
		enteredPosition = distanceMultiplier * DataGetter::getVector3D();
	}
	return enteredPosition;
}

Vector3D ScenarioBuilder::promptForBodyVelocity() const
{
	ConsoleWriter::writeLine();
	const auto velocityMultiplier{ getUnitMultiplier(std::vector<MenuOptionPair>{
		{TextId::MetrePerSecond, 1.0},
		{TextId::KilometrePerSecond, physics::KMS_MULTIPLIER},
		{TextId::ThousandKilometrePerHour, physics::KKMH_MULTIPLIER},
		{TextId::SpeedOfLight, physics::C_CONST}},
		TextId::SelectSpeedUnit) };

	ConsoleWriter::write(TextId::EnterVelocityVector, ": ");
	return velocityMultiplier * DataGetter::getVector3D([velocityMultiplier](const double v) {return std::abs(velocityMultiplier * v) < physics::C_CONST; });
}
