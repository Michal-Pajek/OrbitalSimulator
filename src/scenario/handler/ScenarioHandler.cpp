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

namespace scenario
{
	namespace
	{
		std::string getNewSaveName()
		{
			ui::console::write(localization::TextId::EnterNewSaveName, ": ");
			return ::input::data::getFileBaseName();
		}
	} // anonymous namespace

	void ScenarioHandler::buildAndHandleScenario()
	{
		auto scenario{ builder::buildScenario() };

		if (scenario) {
			ui::console::writeLine(localization::TextId::ScenarioCreatedSuccessfully);
			ScenarioHandler handler{ *scenario };
			handler.handleScenario(ScenarioHandlingConfig{ .printSummary = false });
		}
		else {
			ui::console::writeLine('\n', localization::TextId::ScenarioCreationCanceled);
		}
	}

	void ScenarioHandler::loadAndHandleScenario()
	{
		auto result{ loader::getScenario() };

		switch (result.status) {
		case loader::LoadStatus::Loaded:
		{
			runtime_checks::ensure(result.scenario.has_value(), runtime_checks::Type::Logic, "scenario::loader returned Loaded status without a scenario");

			ui::console::writeLine(localization::TextId::ScenarioLoadedSuccessfully, '\n');
			ScenarioHandler handler{ *result.scenario };
			handler.handleScenario(ScenarioHandlingConfig{ .askToSave = false });
			break;
		}

		case loader::LoadStatus::Canceled:
			ui::console::writeLine(localization::TextId::ScenarioLoadingCanceled);
			break;

		case loader::LoadStatus::NoSavedScenarios:
			ui::console::writeLine(localization::TextId::ThereAreNoSavedScenarios);
			break;

		case loader::LoadStatus::Failed:
			ui::console::writeLine(localization::TextId::ScenarioLoadingFailed);
			break;
		}
	}

	void ScenarioHandler::handleScenario(const ScenarioHandlingConfig& config) const
	{
		if (config.printSummary) {
			summary::print(m_scenario);
		}

		if (config.askToSave &&
			ui::Menu::yesOrNo(localization::TextId::QuestionDoYouWantToSaveTheScenario)) {
			saveScenario();
		}
		if (config.askToRun &&
			ui::Menu::yesOrNo(localization::TextId::QuestionDoYouWantToRunTheSimulationNow)) {
			runSimulationForScenario();
		}
	}

	void ScenarioHandler::runSimulationForScenario() const
	{
		const auto runConfig{ simulation::run_config::build() };
		recording::Recorder recorder{ m_scenario.name };
		simulation::runner::runAndRecord(recorder, m_scenario, runConfig);
	}

	void ScenarioHandler::saveScenario() const
	{
		ui::console::writeLine(localization::TextId::DefaultSaveNameIs, ": ", m_scenario.name);
		saveScenario(ui::Menu::yesOrNo(localization::TextId::QuestionDoYouWantToUseThisSaveName) ? m_scenario.name : getNewSaveName());
	}

	void ScenarioHandler::saveScenario(const std::string& initialSaveName) const
	{
		std::string saveName{ initialSaveName };
		auto result{ saver::save(m_scenario, saveName) };
		bool shouldContinueSaving{ true };
		while (result == saver::SaveResult::FileAlreadyExists && shouldContinueSaving) {
			ui::console::writeLine(localization::TextId::ThisSaveNameAlreadyExists);
			const ui::Menu saveConflictMenu{ {
				ui::MenuOption{'O', localization::TextId::Overwrite,		[this, &result, &saveName]() {
					result = saver::save(m_scenario, saveName, saver::OverwritePolicy::Allow); }},
				ui::MenuOption{'N', localization::TextId::EnterNewSaveName,	[this, &result, &saveName]() {
					saveName = getNewSaveName();
					result = saver::save(m_scenario, saveName); }},
				ui::MenuOption{'V', localization::TextId::SaveAsNewVersion,	[this, &result, &saveName]() {
					saveName = saver::getNextAvailableSaveName(saveName);
					result = saver::save(m_scenario, saveName);	}},
				ui::MenuOption{'C', localization::TextId::Cancel,			[&shouldContinueSaving]() {shouldContinueSaving = false; }}},
				localization::TextId::QuestionWhatDoYouWantToDo };
			saveConflictMenu.execute();
		}
		if (result == saver::SaveResult::Saved) {
			ui::console::writeLine(localization::TextId::ScenarioSavedSuccessfully);
		}
	}
} // namespace scenario
