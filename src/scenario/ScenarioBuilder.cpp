#include "scenario/ScenarioBuilder.hpp"
#include <optional>
#include <stdexcept>
#include <utility>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/DataGetter.hpp"
#include "input/Keyboard.hpp"
#include "localization/TextId.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/BodyBuilder.hpp"
#include "simulation/bodies/BodyEditor.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	enum class Decision {
		Accept,
		Revise,
		Cancel
	};

	enum class PartToChange {
		ScenarioName,
		Bodies,
		Cancel
	};

	Decision getScenarioAcceptanceDecision()
	{
		std::optional<Decision> result{};
		const Menu scenarioAcceptanceMenu{ {
			MenuOption{'A', TextId::Accept,	[&result]() {result = Decision::Accept; }},
			MenuOption{'R', TextId::Revise,	[&result]() {result = Decision::Revise; }},
			MenuOption{'C', TextId::Cancel,	[&result]() {result = Decision::Cancel; }}},
			TextId::QuestionWhatDoYouWantToDo };
		scenarioAcceptanceMenu.execute();
		return result.value();
	}

	PartToChange getWhatToChangeDecision()
	{
		std::optional<PartToChange> result{};
		const Menu whatToChangeMenu{ {
			MenuOption{'N',	TextId::ScenarioName,	[&result]() {result = PartToChange::ScenarioName; }},
			MenuOption{'B', TextId::Bodies,			[&result]() {result = PartToChange::Bodies; }},
			MenuOption{'C', TextId::Cancel,			[&result]() {result = PartToChange::Cancel; }}},
			TextId::QuestionWhatDoYouWantToChange };
		whatToChangeMenu.execute();
		return result.value();
	}
} // anonymous namespace

std::optional<Scenario> ScenarioBuilder::buildScenario()
{
	resetState();
	promptForScenarioName();
	createBodiesFromInput();
	if (reviewAndConfirmScenario()) {
		return Scenario{ std::move(m_name), std::move(m_bodies) };
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
	ConsoleWriter::writeLine(TextId::Bodies, ':');
	printBodies(false);
}

void ScenarioBuilder::promptForScenarioName()
{
	ConsoleWriter::write(TextId::EnterScenarioName, ": ");
	m_name = DataGetter::getSingleWordText();
}

void ScenarioBuilder::resetState()
{
	m_bodies.clear();
	m_name.clear();
}

void ScenarioBuilder::reviewAndEditBodies()
{
	bool continueChecking{ true };
	while (continueChecking) {
		auto bodyCount{ static_cast<int>(m_bodies.size()) };

		if (bodyCount == 0) {
			ConsoleWriter::writeLine(TextId::ScenarioMustHaveAtLeastOneBody, ". ", TextId::PressAnyKeyToContinue);
			getSingleKey();
			const BodyBuilder bodyBuilder{ m_bodies };
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
				const BodyBuilder bodyBuilder{ m_bodies };
				m_bodies.emplace_back(bodyBuilder.createBodyFromInput()); }},
			MenuOption{'D', TextId::DeleteBody,	[this, chooseBodyIdx]() {
				m_bodies.erase(m_bodies.begin() + chooseBodyIdx());
				ConsoleWriter::writeLine(TextId::BodyDeleted, '\n'); }},
			MenuOption{'E', TextId::EditBody,	[this, chooseBodyIdx]() {
				const auto idx{ chooseBodyIdx() };
				BodyEditor bodyEditor{ m_bodies.at(idx), m_bodies };
				bodyEditor.editBody();
				m_bodies.at(idx) = bodyEditor.takeBody(); }}},
			TextId::QuestionWhatDoYouWantToDoWithBodies };
		whatToDoWithBodies.execute();
	}
}

void ScenarioBuilder::reviseScenario()
{
	const auto partToChange{ getWhatToChangeDecision() };

	switch (partToChange) {
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
