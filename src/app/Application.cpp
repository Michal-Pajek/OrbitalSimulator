#include "app/Application.hpp"
#include "simulation/Simulation.hpp"

void Application::run()
{
	Simulation simulation{};
	simulation.run();
}
