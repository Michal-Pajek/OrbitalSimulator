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
			if (Menu::yesOrNo(TextId::QuestionDoYouWantToFinish)) {
				ConsoleWriter::write(TextId::ApplicationFinished, ". ", TextId::PressAnyKeyToContinue);
				input::keyboard::getSingleKey();
				m_continue = false;
			} } };
		const Menu mainMenu{ {
				MenuOption{'B', TextId::ScenarioBuilder,	Application::buildScenario},
				MenuOption{'O', TextId::LoadScenario,		Application::loadScenario},
				MenuOption{'L', TextId::SelectLanguage,		Application::selectLanguage},
				MenuOption{'E', TextId::Exit,				closeApplication}
				}, TextId::MainMenu };
		while (m_continue) {
			input::console::clearScreen();
			mainMenu.execute();
		}
	}

	void Application::buildScenario()
	{
		enterModule(TextId::ScenarioBuilder);
		exception_handler::execute(ScenarioHandler::buildAndHandleScenario);
		exitModule();
	}

	void Application::enterModule(const TextId titleId)
	{
		input::console::clearScreen();
		ConsoleWriter::writeHeadline(titleId);
	}

	void Application::exitModule()
	{
		ConsoleWriter::write('\n', TextId::PressAnyKeyToReturnToMainMenu);
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
		auto& localizationManager{ LocalizationManager::getInstance() };
		const Menu languageMenu{ {
			MenuOption{'E', TextId::English,	[&localizationManager]() {localizationManager.setLanguage(LocalizationManager::Language::English); } },
			MenuOption{'P', TextId::Polish,		[&localizationManager]() {localizationManager.setLanguage(LocalizationManager::Language::Polish); } }
			}, TextId::SelectLanguage };
		languageMenu.execute();
		ConsoleWriter::writeLine('\n', TextId::SelectedLanguage, ": ", localizationManager.getCurrentLanguageTextId());
		exitModule();
	}
} // namespace app
