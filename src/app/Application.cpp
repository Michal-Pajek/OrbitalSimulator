#include "app/Application.hpp"
#include "scenario/Scenario.hpp"

void Application::run()
{
	Scenario scenario{};
	scenario.run();
}
