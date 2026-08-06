#include "scenario/ScenarioHandler.hpp"
#include "app/Menu.hpp"
#include "input/DataGetter.hpp"
#include "localization/TextId.hpp"
#include "recording/Recorder.hpp"
#include "runner/SimulationRunner.hpp"
#include "scenario/Scenario.hpp"
#include "scenario/ScenarioSaver.hpp"
#include "scenario/ScenarioSummary.hpp"
#include "simulation/SimulationRunConfigBuilder.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	std::string getNewSaveName()
	{
		ConsoleWriter::write(TextId::EnterNewSaveName, ": ");
		return DataGetter::getFileBaseName();
	}
}

void ScenarioHandler::handleScenario(const ScenarioHandlingConfig& config) const
{
	if (config.printSummary) {
		ScenarioSummary::print(m_scenario);
	}

	if (config.askToSave &&
		Menu::yesOrNo(TextId::QuestionDoYouWantToSaveTheScenario)) {
		saveScenario();
	}
	if (config.askToRun &&
		Menu::yesOrNo(TextId::QuestionDoYouWantToRunTheSimulationNow)) {
		runSimulationForScenario();
	}
}

void ScenarioHandler::runSimulationForScenario() const
{
	const auto runConfig{ SimulationRunConfigBuilder::build() };
	Recorder recorder{ m_scenario.name };
	SimulationRunner::runAndRecord(recorder, m_scenario, runConfig);
}

void ScenarioHandler::saveScenario() const
{
	ConsoleWriter::writeLine(TextId::DefaultSaveNameIs, ": ", m_scenario.name);
	saveScenario(Menu::yesOrNo(TextId::QuestionDoYouWantToUseThisSaveName) ? m_scenario.name : getNewSaveName());
}

void ScenarioHandler::saveScenario(const std::string& initialSaveName) const
{
	std::string saveName{ initialSaveName };
	auto result{ ScenarioSaver::save(m_scenario, saveName) };
	bool shouldContinueSaving{ true };
	while (result == ScenarioSaver::SaveResult::FileAlreadyExists && shouldContinueSaving) {
		ConsoleWriter::writeLine(TextId::ThisSaveNameAlreadyExists);
		const Menu saveConflictMenu{ {
			MenuOption{'O', TextId::Overwrite,			[this, &result, &saveName]() {
				result = ScenarioSaver::save(m_scenario, saveName, ScenarioSaver::OverwritePolicy::Allow); }},
			MenuOption{'N', TextId::EnterNewSaveName,	[this, &result, &saveName]() {
				saveName = getNewSaveName();
				result = ScenarioSaver::save(m_scenario, saveName); }},
			MenuOption{'V', TextId::SaveAsNewVersion,	[this, &result, &saveName]() {
				saveName = ScenarioSaver::getNextAvailableSaveName(saveName);
				result = ScenarioSaver::save(m_scenario, saveName);	}},
			MenuOption{'C', TextId::Cancel,				[&shouldContinueSaving]() {shouldContinueSaving = false; }}},
			TextId::QuestionWhatDoYouWantToDo };
		saveConflictMenu.execute();
	}
	if (result == ScenarioSaver::SaveResult::Saved) {
		ConsoleWriter::writeLine(TextId::ScenarioSavedSuccessfully);
	}
}
