#include "app/Application.hpp"

#include "app/ExceptionHandler.hpp"

#include "input/core/Console.hpp"
#include "input/core/Keyboard.hpp"
#include "localization/LocalizationManager.hpp"
#include "scenario/handler/ScenarioHandler.hpp"
#include "ui/ConsoleWriter.hpp"
#include "ui/menu/Menu.hpp"

namespace app
{
	void Application::eventLoop()
	{
		const auto closeApplication{ [this]() {
			input::console::clearScreen();
			if (ui::Menu::yesOrNo(localization::TextId::QuestionDoYouWantToFinish)) {
				ui::console::write(localization::TextId::ApplicationFinished, ". ", localization::TextId::PressAnyKeyToContinue);
				input::keyboard::getSingleKey();
				m_continue = false;
			} } };
		const ui::Menu mainMenu{ {
				ui::MenuOption{'B', localization::TextId::ScenarioBuilder,	Application::buildScenario},
				ui::MenuOption{'O', localization::TextId::LoadScenario,		Application::loadScenario},
				ui::MenuOption{'L', localization::TextId::SelectLanguage,	Application::selectLanguage},
				ui::MenuOption{'E', localization::TextId::Exit,				closeApplication}
				}, localization::TextId::MainMenu };
		while (m_continue) {
			input::console::clearScreen();
			mainMenu.execute();
		}
	}

	void Application::buildScenario()
	{
		enterModule(localization::TextId::ScenarioBuilder);
		exception_handler::execute(scenario::ScenarioHandler::buildAndHandleScenario);
		exitModule();
	}

	void Application::enterModule(const localization::TextId titleId)
	{
		input::console::clearScreen();
		ui::console::writeHeadline(titleId);
	}

	void Application::exitModule()
	{
		ui::console::write('\n', localization::TextId::PressAnyKeyToReturnToMainMenu);
		input::keyboard::getSingleKey();
	}

	void Application::loadScenario()
	{
		input::console::clearScreen();
		exception_handler::execute(scenario::ScenarioHandler::loadAndHandleScenario);

		exitModule();
	}

	void Application::selectLanguage()
	{
		input::console::clearScreen();
		auto& localizationManager{ localization::LocalizationManager::getInstance() };
		const ui::Menu languageMenu{ {
			ui::MenuOption{'E', localization::TextId::English,	[&localizationManager]() {localizationManager.setLanguage(localization::LocalizationManager::Language::English); } },
			ui::MenuOption{'P', localization::TextId::Polish,	[&localizationManager]() {localizationManager.setLanguage(localization::LocalizationManager::Language::Polish); } }
			}, localization::TextId::SelectLanguage };
		languageMenu.execute();
		ui::console::writeLine('\n', localization::TextId::SelectedLanguage, ": ", localizationManager.getCurrentLanguageTextId());
		exitModule();
	}
} // namespace app
