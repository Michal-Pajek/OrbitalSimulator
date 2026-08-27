#include "scenario/handler/ScenarioHandler.hpp"

#include "scenario/builder/ScenarioBuilder.hpp"
#include "scenario/core/Scenario.hpp"
#include "scenario/loader/ScenarioLoader.hpp"
#include "scenario/saver/ScenarioSaver.hpp"
#include "scenario/summary/ScenarioSummary.hpp"

#include "common/runtime_checks/RuntimeChecks.hpp"
#include "input/data/DataGetter.hpp"
#include "localization/core/TextId.hpp"
#include "recording/Recorder.hpp"
#include "runner/SimulationRunner.hpp"
#include "simulation/run_config/builder/SimulationRunConfigBuilder.hpp"
#include "ui/ConsoleWriter.hpp"
#include "ui/menu/Menu.hpp"

namespace
{
	std::string getNewSaveName()
	{
		ConsoleWriter::write(TextId::EnterNewSaveName, ": ");
		return input::data::getFileBaseName();
	}
} // anonymous namespace

void ScenarioHandler::buildAndHandleScenario()
{
	auto scenario{ ScenarioBuilder::buildScenario() };

	if (scenario) {
		ConsoleWriter::writeLine(TextId::ScenarioCreatedSuccessfully);
		ScenarioHandler handler{ *scenario };
		handler.handleScenario(ScenarioHandlingConfig{ .printSummary = false });
	}
	else {
		ConsoleWriter::writeLine('\n', TextId::ScenarioCreationCanceled);
	}
}

void ScenarioHandler::loadAndHandleScenario()
{
	auto result{ ScenarioLoader::getScenario() };

	switch (result.status) {
	case ScenarioLoader::LoadStatus::Loaded:
	{
		runtime_checks::ensure(result.scenario.has_value(), runtime_checks::Type::Logic, "ScenarioLoader returned Loaded status without a scenario");

		ConsoleWriter::writeLine(TextId::ScenarioLoadedSuccessfully, '\n');
		ScenarioHandler handler{ *result.scenario };
		handler.handleScenario(ScenarioHandlingConfig{ .askToSave = false });
		break;
	}

	case ScenarioLoader::LoadStatus::Canceled:
		ConsoleWriter::writeLine(TextId::ScenarioLoadingCanceled);
		break;

	case ScenarioLoader::LoadStatus::NoSavedScenarios:
		ConsoleWriter::writeLine(TextId::ThereAreNoSavedScenarios);
		break;

	case ScenarioLoader::LoadStatus::Failed:
		ConsoleWriter::writeLine(TextId::ScenarioLoadingFailed);
		break;
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
