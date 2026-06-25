#include "app/Application.hpp"
#include <exception>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/Keyboard.hpp"
#include "recording/Recorder.hpp"
#include "runner/SimulationRunner.hpp"
#include "scenario/Scenario.hpp"
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
			MenuOption{'S', TextId::RunTestScenario,	Application::testScenario},
			MenuOption{'O', TextId::Options,			Application::options},
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

void Application::options()
{
	enterModule(TextId::Options);
	ConsoleWriter::write(TextId::NotImplemented);
	exitModule();
}

// TODO: Remove after the Scenario refactor
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