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
			if (Menu::yesOrNo(localization::TextId::QuestionDoYouWantToFinish)) {
				ConsoleWriter::write(localization::TextId::ApplicationFinished, ". ", localization::TextId::PressAnyKeyToContinue);
				input::keyboard::getSingleKey();
				m_continue = false;
			} } };
		const Menu mainMenu{ {
				MenuOption{'B', localization::TextId::ScenarioBuilder,	Application::buildScenario},
				MenuOption{'O', localization::TextId::LoadScenario,		Application::loadScenario},
				MenuOption{'L', localization::TextId::SelectLanguage,	Application::selectLanguage},
				MenuOption{'E', localization::TextId::Exit,				closeApplication}
				}, localization::TextId::MainMenu };
		while (m_continue) {
			input::console::clearScreen();
			mainMenu.execute();
		}
	}

	void Application::buildScenario()
	{
		enterModule(localization::TextId::ScenarioBuilder);
		exception_handler::execute(ScenarioHandler::buildAndHandleScenario);
		exitModule();
	}

	void Application::enterModule(const localization::TextId titleId)
	{
		input::console::clearScreen();
		ConsoleWriter::writeHeadline(titleId);
	}

	void Application::exitModule()
	{
		ConsoleWriter::write('\n', localization::TextId::PressAnyKeyToReturnToMainMenu);
		input::keyboard::getSingleKey();
	}

	void Application::loadScenario()
	{
		input::console::clearScreen();
		exception_handler::execute(ScenarioHandler::loadAndHandleScenario);

		exitModule();
	}

	void Application::selectLanguage()
	{
		input::console::clearScreen();
		auto& localizationManager{ localization::LocalizationManager::getInstance() };
		const Menu languageMenu{ {
			MenuOption{'E', localization::TextId::English,	[&localizationManager]() {localizationManager.setLanguage(localization::LocalizationManager::Language::English); } },
			MenuOption{'P', localization::TextId::Polish,		[&localizationManager]() {localizationManager.setLanguage(localization::LocalizationManager::Language::Polish); } }
			}, localization::TextId::SelectLanguage };
		languageMenu.execute();
		ConsoleWriter::writeLine('\n', localization::TextId::SelectedLanguage, ": ", localizationManager.getCurrentLanguageTextId());
		exitModule();
	}
} // namespace app
