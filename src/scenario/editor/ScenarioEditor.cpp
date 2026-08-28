#include "scenario/editor/ScenarioEditor.hpp"

#include <stdexcept>

#include "scenario/input/ScenarioInput.hpp"
#include "scenario/summary/ScenarioSummary.hpp"

#include "body/input/BodyBuilder.hpp"
#include "body/input/BodyEditor.hpp"
#include "common/runtime_checks/RuntimeChecks.hpp"
#include "input/core/Console.hpp"
#include "input/core/Keyboard.hpp"
#include "input/data/DataGetter.hpp"
#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"
#include "ui/menu/Menu.hpp"

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
			MenuOption{'A', localization::TextId::Accept,	[&result]() {result = Decision::Accept; }},
			MenuOption{'R', localization::TextId::Revise,	[&result]() {result = Decision::Revise; }},
			MenuOption{'C', localization::TextId::Cancel,	[&result]() {result = Decision::Cancel; }}},
			localization::TextId::QuestionWhatDoYouWantToDo };
		scenarioAcceptanceMenu.execute();
		return result.value();
	}

	PartToChange getWhatToChangeDecision()
	{
		std::optional<PartToChange> result{};
		const Menu whatToChangeMenu{ {
			MenuOption{'N',	localization::TextId::ScenarioName,	[&result]() {result = PartToChange::ScenarioName; }},
			MenuOption{'B', localization::TextId::Bodies,		[&result]() {result = PartToChange::Bodies; }},
			MenuOption{'C', localization::TextId::Cancel,		[&result]() {result = PartToChange::Cancel; }}},
			localization::TextId::QuestionWhatDoYouWantToChange };
		whatToChangeMenu.execute();
		return result.value();
	}
} // anonymous namespace

std::optional<Scenario> ScenarioEditor::getReviewedScenario()
{
	while (true) {
		input::console::clearScreen();
		ScenarioSummary::print(m_scenario);

		const auto decision{ getScenarioAcceptanceDecision() };
		switch (decision) {
		case Decision::Accept:
			runtime_checks::ensure(!m_scenario.bodies.empty(), runtime_checks::Type::Logic, "Scenario must contain at least one body");
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
		MenuOption{'A', localization::TextId::Accept,		[&shouldContinue]()	{shouldContinue = false; }},
		MenuOption{'B', localization::TextId::AddBody,		[this]()			{addNewBody(); },				canAddBody()},
		MenuOption{'D', localization::TextId::DeleteBody,	[this]()			{deleteSelectedBody(); }},
		MenuOption{'E', localization::TextId::EditBody,		[this]()			{editSelectedBody(); }}},
		localization::TextId::QuestionWhatDoYouWantToDoWithBodies };
	whatToDoWithBodies.execute();
	return shouldContinue;
}

void ScenarioEditor::addNewBody()
{
	auto& bodies{ m_scenario.bodies };
	runtime_checks::ensure(bodies.size() < Scenario::MAX_BODY_COUNT, runtime_checks::Type::Logic, "Bodies vector is already full");
	const body::input::BodyBuilder bodyBuilder{ bodies };
	bodies.emplace_back(bodyBuilder.createBodyFromInput());
}

void ScenarioEditor::deleteSelectedBody()
{
	auto& bodies{ m_scenario.bodies };
	runtime_checks::ensure(!bodies.empty(), runtime_checks::Type::Logic, "There is no body to delete");
	bodies.erase(bodies.begin() + promptForBodyIdx());
	ConsoleWriter::writeLine(localization::TextId::BodyDeleted, '\n');
}

void ScenarioEditor::editSelectedBody()
{
	auto& bodies{ m_scenario.bodies };
	const auto idx{ promptForBodyIdx() };
	body::input::BodyEditor bodyEditor{ bodies.at(idx), bodies };
	bodyEditor.editBody();
	bodies.at(idx) = bodyEditor.takeBody();
}

void ScenarioEditor::ensureAtLeastOneBody()
{
	if (m_scenario.bodies.empty()) {
		ConsoleWriter::writeLine(localization::TextId::ScenarioMustHaveAtLeastOneBody, ". ", localization::TextId::PressAnyKeyToContinue);
		input::keyboard::getSingleKey();
		addNewBody();
	}
}

void ScenarioEditor::printBodies() const
{
	ConsoleWriter::writeHeadline(localization::TextId::CurrentBodiesList);
	const auto& bodies{ m_scenario.bodies };
	ConsoleWriter::writeLine(localization::TextId::ObjectCount, ":\t", bodies.size());
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
	return input::data::getSelectionNumber(localization::TextId::EnterBodyNumber, m_scenario.bodies.size()) - 1u;
}
