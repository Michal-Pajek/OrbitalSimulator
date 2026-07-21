#include "scenario/ScenarioHandler.hpp"
#include "app/Menu.hpp"
#include "input/DataGetter.hpp"
#include "localization/TextId.hpp"
#include "recording/Recorder.hpp"
#include "runner/SimulationRunner.hpp"
#include "scenario/Scenario.hpp"
#include "scenario/ScenarioSaver.hpp"
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

void ScenarioHandler::handleScenario() const
{
	if (Menu::yesOrNo(TextId::QuestionDoYouWantToSaveTheScenario)) {
		saveScenario();
	}
	if (Menu::yesOrNo(TextId::QuestionDoYouWantToRunTheSimulationNow)) {
		runSimulationForScenario();
	}
}

void ScenarioHandler::runSimulationForScenario() const
{
	const auto runConfig{ SimulationRunConfigBuilder::build() };
	const std::string fileName{ m_scenario.name };
	Recorder recorder{ fileName };
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
