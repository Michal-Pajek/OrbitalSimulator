#include "scenario/ScenarioEditor.hpp"
#include <stdexcept>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/DataGetter.hpp"
#include "input/Keyboard.hpp"
#include "localization/TextId.hpp"
#include "scenario/ScenarioInput.hpp"
#include "scenario/ScenarioSummary.hpp"
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
}

std::optional<Scenario> ScenarioEditor::getReviewedScenario()
{
	while (true) {
		clearScreen();
		ScenarioSummary::print(m_scenario);

		const auto decision{ getScenarioAcceptanceDecision() };
		switch (decision) {
		case Decision::Accept:
			if (m_scenario.bodies.empty()) {
				throw std::logic_error{ "Scenario must contain at least one body" };
			}
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
	auto& bodies{ m_scenario.bodies };
	while (continueChecking) {
		auto bodyCount{ static_cast<int>(bodies.size()) };

		if (bodyCount == 0) {
			ConsoleWriter::writeLine(TextId::ScenarioMustHaveAtLeastOneBody, ". ", TextId::PressAnyKeyToContinue);
			getSingleKey();
			const BodyBuilder bodyBuilder{ bodies };
			bodies.emplace_back(bodyBuilder.createBodyFromInput());
			++bodyCount;
		}

		printBodies();

		const auto chooseBodyIdx{ [bodyCount]() {
			ConsoleWriter::write(TextId::EnterBodyNumber, ": ");
			return static_cast<size_t>(DataGetter::getValue<int>([bodyCount](const int value) {return 0 < value && value <= bodyCount; }) - 1);
			} };

		Menu whatToDoWithBodies{ {
			MenuOption{'A', TextId::Accept,		[&continueChecking]() {continueChecking = false; }},
			MenuOption{'B', TextId::AddBody,	[&bodies]() {
				const BodyBuilder bodyBuilder{ bodies };
				bodies.emplace_back(bodyBuilder.createBodyFromInput()); }},
			MenuOption{'D', TextId::DeleteBody,	[&bodies, chooseBodyIdx]() {
				bodies.erase(bodies.begin() + chooseBodyIdx());
				ConsoleWriter::writeLine(TextId::BodyDeleted, '\n'); }},
			MenuOption{'E', TextId::EditBody,	[&bodies, chooseBodyIdx]() {
				const auto idx{ chooseBodyIdx() };
				BodyEditor bodyEditor{ bodies.at(idx), bodies };
				bodyEditor.editBody();
				bodies.at(idx) = bodyEditor.takeBody(); }}},
			TextId::QuestionWhatDoYouWantToDoWithBodies };
		whatToDoWithBodies.execute();
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
