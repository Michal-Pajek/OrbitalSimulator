#pragma once
#include <string>
#include <vector>
#include "simulation/bodies/Body.hpp"

namespace ScenarioInput
{
	std::string promptForScenarioName();
	std::vector<Body> createBodiesFromInput();
};
