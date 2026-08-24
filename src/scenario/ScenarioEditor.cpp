#include "scenario/ScenarioEditor.hpp"

#include <stdexcept>

#include "scenario/ScenarioInput.hpp"
#include "scenario/ScenarioSummary.hpp"

#include "app/Menu.hpp"
#include "common/RuntimeChecks.hpp"
#include "input/core/Console.hpp"
#include "input/DataGetter.hpp"
#include "input/core/Keyboard.hpp"
#include "localization/core/TextId.hpp"
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

std::optional<Scenario> ScenarioEditor::getReviewedScenario()
{
	while (true) {
		Console::clearScreen();
		ScenarioSummary::print(m_scenario);

		const auto decision{ getScenarioAcceptanceDecision() };
		switch (decision) {
		case Decision::Accept:
			RuntimeChecks::ensure(!m_scenario.bodies.empty(), RuntimeChecks::Type::Logic, "Scenario must contain at least one body");
			return std::move(m_scenario);
		case Decision::Revise:
			reviseScenario();
			break;
		case Decision::Cancel:
			return std::nullopt;
		default:
			throw std::logic_error{ "Wrong decision selected" };
		}
	}
}

bool ScenarioEditor::handleBodiesMenu()
{
	bool shouldContinue{ true };

	Menu whatToDoWithBodies{ {
		MenuOption{'A', TextId::Accept,		[&shouldContinue]()	{shouldContinue = false; }},
		MenuOption{'B', TextId::AddBody,	[this]()			{addNewBody(); },				canAddBody()},
		MenuOption{'D', TextId::DeleteBody,	[this]()			{deleteSelectedBody(); }},
		MenuOption{'E', TextId::EditBody,	[this]()			{editSelectedBody(); }}},
		TextId::QuestionWhatDoYouWantToDoWithBodies };
	whatToDoWithBodies.execute();
	return shouldContinue;
}

void ScenarioEditor::addNewBody()
{
	auto& bodies{ m_scenario.bodies };
	RuntimeChecks::ensure(bodies.size() < Scenario::MAX_BODY_COUNT, RuntimeChecks::Type::Logic, "Bodies vector is already full");
	const BodyBuilder bodyBuilder{ bodies };
	bodies.emplace_back(bodyBuilder.createBodyFromInput());
}

void ScenarioEditor::deleteSelectedBody()
{
	auto& bodies{ m_scenario.bodies };
	RuntimeChecks::ensure(!bodies.empty(), RuntimeChecks::Type::Logic, "There is no body to delete");
	bodies.erase(bodies.begin() + promptForBodyIdx());
	ConsoleWriter::writeLine(TextId::BodyDeleted, '\n');
}

void ScenarioEditor::editSelectedBody()
{
	auto& bodies{ m_scenario.bodies };
	const auto idx{ promptForBodyIdx() };
	BodyEditor bodyEditor{ bodies.at(idx), bodies };
	bodyEditor.editBody();
	bodies.at(idx) = bodyEditor.takeBody();
}

void ScenarioEditor::ensureAtLeastOneBody()
{
	if (m_scenario.bodies.empty()) {
		ConsoleWriter::writeLine(TextId::ScenarioMustHaveAtLeastOneBody, ". ", TextId::PressAnyKeyToContinue);
		Keyboard::getSingleKey();
		addNewBody();
	}
}

void ScenarioEditor::printBodies() const
{
	ConsoleWriter::writeHeadline(TextId::CurrentBodiesList);
	const auto& bodies{ m_scenario.bodies };
	ConsoleWriter::writeLine(TextId::ObjectCount, ":\t", bodies.size());
	auto counter{ 1 };

	for (const auto& body : bodies) {
		ConsoleWriter::write('\t', counter++, ":\t");
		body.printSummary(true);
	}
}

void ScenarioEditor::reviewAndEditBodies()
{
	bool continueChecking{ true };
	while (continueChecking) {
		ensureAtLeastOneBody();
		printBodies();
		continueChecking = handleBodiesMenu();
	}
}

void ScenarioEditor::reviseScenario()
{
	const auto partToChange{ getWhatToChangeDecision() };

	switch (partToChange) {
	case PartToChange::ScenarioName:
		m_scenario.name = ScenarioInput::promptForScenarioName();
		break;
	case PartToChange::Bodies:
		reviewAndEditBodies();
		break;
	case PartToChange::Cancel:
		return;
	default:
		throw std::logic_error{ "Wrong decision selected" };
	}
}

std::size_t ScenarioEditor::promptForBodyIdx() const
{
	return DataGetter::getSelectionNumber(TextId::EnterBodyNumber, m_scenario.bodies.size()) - 1u;
}
