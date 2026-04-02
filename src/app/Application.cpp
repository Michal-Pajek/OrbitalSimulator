#include "app/Application.hpp"
#include <iostream>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/Keyboard.hpp"
#include "scenario/Scenario.hpp"

void Application::eventLoop()
{
	const auto closeApplication{ [this]() {
		clearScreen();
		std::cout << "Do you want to finish?";
		if (Menu::yesOrNo()) {
			std::cout << "Yes\nThe program has finished running. Press any key...";
			getSingleKey();
			m_continue = false;
		} } };
	const Menu mainMenu{ {
			MenuOption{.key = 'S', .label = "Run test scenario",	.func = Application::testScenario},
			MenuOption{.key = 'O', .label = "Options",				.func = Application::options},
			MenuOption{.key = 'E', .label = "Exit",					.func = closeApplication}
			}, std::string{"Main Menu"} };
	while (m_continue) {
		clearScreen();
		mainMenu.execute();
	}
}

void Application::testScenario()
{
	enterModule(std::string{ "Test scenario" });
	Scenario scenario{};
	scenario.run();
	exitModule();
}

void Application::options()
{
	enterModule(std::string{ "Options" });
	std::cout << "Not implemented yet\n";
	exitModule();
}

void Application::enterModule(const std::string& text)
{
	clearScreen();
	std::cout << "\t=== " << text << " ===\n\n";
}

void Application::exitModule()
{
	std::cout << "\nPress any key to back to main menu...";
	getSingleKey();
}