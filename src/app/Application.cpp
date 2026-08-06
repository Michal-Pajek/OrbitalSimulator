#include "app/Application.hpp"
#include <exception>
#include <stdexcept>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/Keyboard.hpp"
#include "localization/LocalizationManager.hpp"
#include "localization/TextId.hpp"
#include "scenario/ScenarioBuilder.hpp"
#include "scenario/ScenarioHandler.hpp"
#include "scenario/ScenarioLoader.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	void loadAndHandleScenario()
	{
		auto result{ ScenarioLoader::getScenario() };

		switch (result.status) {
		case ScenarioLoader::LoadStatus::Loaded:
		{
			if (!result.scenario) {
				throw std::logic_error{ "ScenarioLoader returned Loaded status without a scenario" };
			}

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
}

void Application::eventLoop()
{
	const auto closeApplication{ [this]() {
		clearScreen();
		if (Menu::yesOrNo(TextId::QuestionDoYouWantToFinish)) {
			ConsoleWriter::write(TextId::ApplicationFinished, ". ", TextId::PressAnyKeyToContinue);
			getSingleKey();
			m_continue = false;
		} } };
	const Menu mainMenu{ {
			MenuOption{'B', TextId::ScenarioBuilder,	Application::buildScenario},
			MenuOption{'O', TextId::LoadScenario,		Application::loadScenario},
			MenuOption{'L', TextId::SelectLanguage,		Application::selectLanguage},
			MenuOption{'E', TextId::Exit,				closeApplication}
			}, TextId::MainMenu};
	while (m_continue) {
		clearScreen();
		mainMenu.execute();
	}
}

void Application::buildScenario()
{
	enterModule(TextId::ScenarioBuilder);

	try {
		ScenarioBuilder builder{};
		auto scenario{ builder.buildScenario() };
		if (scenario) {
			ConsoleWriter::writeLine(TextId::ScenarioCreatedSuccessfully);
			ScenarioHandler handler{ *scenario };
			handler.handleScenario(ScenarioHandlingConfig{ .printSummary = false });
		}
		else {
			ConsoleWriter::writeLine('\n', TextId::ScenarioCreationCanceled);
		}
	}
	catch (const std::exception& e) {
		ConsoleWriter::writeError(e.what());
	}
	exitModule();
}

void Application::enterModule(const TextId titleId)
{
	clearScreen();
	ConsoleWriter::writeHeadline(titleId);
}

void Application::exitModule()
{
	ConsoleWriter::write('\n', TextId::PressAnyKeyToReturnToMainMenu);
	getSingleKey();
}

void Application::loadScenario()
{
	clearScreen();
	try {
		loadAndHandleScenario();
	}
	catch (const std::exception& e) {
		ConsoleWriter::writeError(e.what());
	}

	exitModule();
}

void Application::selectLanguage()
{
	clearScreen();
	auto& localizationManager{ LocalizationManager::getInstance() };
	const Menu languageMenu{ {
		MenuOption{'E', TextId::English,	[&localizationManager]() {localizationManager.setLanguage(LocalizationManager::Language::English); } },
		MenuOption{'P', TextId::Polish,		[&localizationManager]() {localizationManager.setLanguage(LocalizationManager::Language::Polish); } }
		}, TextId::SelectLanguage };
	languageMenu.execute();
	ConsoleWriter::writeLine('\n', TextId::SelectedLanguage, ": ", localizationManager.getCurrentLanguageTextId());
	exitModule();
}
