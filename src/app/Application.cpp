#include "app/Application.hpp"
#include <exception>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/Keyboard.hpp"
#include "recording/Recorder.hpp"
#include "runner/SimulationRunner.hpp"
#include "scenario/Scenario.hpp"
#include "ui/ConsoleWriter.hpp"

void Application::eventLoop()
{
	const auto closeApplication{ [this]() {
		clearScreen();
		if (Menu::yesOrNo(TextId::FinishQuestion)) {
			ConsoleWriter::write(TextId::FinishRunning);
			getSingleKey();
			m_continue = false;
		} } };
	const Menu mainMenu{ {
			MenuOption{.key = 'S', .label = TextId::RunTestScenario,	.func = Application::testScenario},
			MenuOption{.key = 'O', .label = TextId::Options,			.func = Application::options},
			MenuOption{.key = 'E', .label = TextId::Exit,				.func = closeApplication}
			}, TextId::MainMenu};
	while (m_continue) {
		clearScreen();
		mainMenu.execute();
	}
}

void Application::testScenario()
{
	enterModule(TextId::RunTestScenario);
	Scenario scenario{};
	Recorder recorder{ "TestScenario.csv" };
	try {
		SimulationRunner::runAndRecord(recorder, scenario);
	}
	catch (const std::exception& e) {
		ConsoleWriter::writeError(e.what());
	}
	exitModule();
}

void Application::options()
{
	enterModule(TextId::Options);
	ConsoleWriter::write(TextId::NotImplemented);
	exitModule();
}

void Application::enterModule(const TextId titleId)
{
	clearScreen();
	ConsoleWriter::writeHeadline(titleId);
}

void Application::exitModule()
{
	ConsoleWriter::write(TextId::BackToMainMenu);
	getSingleKey();
}