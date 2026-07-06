#include "app/Application.hpp"
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/Keyboard.hpp"
#include "localization/LocalizationManager.hpp"
#include "scenario/ScenarioBuilder.hpp"
#include "ui/ConsoleWriter.hpp"

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
	ScenarioBuilder builder{};
	const auto scenario{ builder.buildScenario() };
	if (scenario.has_value()) {
		// todo
		ConsoleWriter::writeLine(TextId::ScenarioCreatedSuccessfully);
	}
	else {
		// todo
		ConsoleWriter::writeLine(TextId::ScenarioCreationCanceled);
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
