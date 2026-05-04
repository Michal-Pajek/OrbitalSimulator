#include "scenario/ScenarioBuilder.hpp"
#include <stdexcept>
#include <utility>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/DataGetter.hpp"
#include "input/Keyboard.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/BodyBuilder.hpp"
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

void ScenarioBuilder::createBodiesFromInput()
{
	constexpr auto MAX_BODYCOUNT{ 20 };
	m_bodies.clear();
	ConsoleWriter::writeLine();
	ConsoleWriter::write(TextId::EnterObjectCountNotGreaterThan, ' ', MAX_BODYCOUNT, ": ");
	const auto bodiesCount{ static_cast<unsigned int>(DataGetter::getValue<int>([](const int x) {return x > 0 && x <= MAX_BODYCOUNT; })) };
	m_bodies.reserve(bodiesCount);
	for (unsigned int i{}; i < bodiesCount; ++i) {
		const BodyBuilder bodyBuilder{ m_bodies };
		m_bodies.emplace_back(bodyBuilder.createBodyFromInput());
	}

	clearScreen();
	reviewAndEditBodies();
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
			const BodyBuilder bodyBuilder{m_bodies};
			m_bodies.emplace_back(bodyBuilder.createBodyFromInput());
			++bodyCount;
		}

		printBodies();

		const auto chooseBodyIdx{ [bodyCount]() {
			ConsoleWriter::write(TextId::EnterBodyNumber, ": ");
			return static_cast<size_t>(DataGetter::getValue<int>([bodyCount](const int value) {return 0 < value && value <= bodyCount; }) - 1);
			} };

		Menu whatToDoWithBodies{ {
			MenuOption{'A', TextId::Accept,		[&continueChecking]() {continueChecking = false; }},
			MenuOption{'B', TextId::AddBody,	[this]() {
				const BodyBuilder bodyBuilder{m_bodies};
				m_bodies.emplace_back(bodyBuilder.createBodyFromInput()); }},
			MenuOption{'D', TextId::DeleteBody,	[this, chooseBodyIdx]() {
				m_bodies.erase(m_bodies.begin() + chooseBodyIdx());
				ConsoleWriter::writeLine(TextId::BodyDeleted, '\n'); }},
			MenuOption{'E', TextId::EditBody,	[this, chooseBodyIdx]() {
				const BodyBuilder bodyBuilder{m_bodies};
				bodyBuilder.editBody(m_bodies.at(chooseBodyIdx())); }}},
			TextId::QuestionWhatDoYouWantToDoWithBodies };
		whatToDoWithBodies.execute();
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