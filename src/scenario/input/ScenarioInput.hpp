#pragma once
#include <string>
#include <vector>

#include "body/Body.hpp"

namespace ScenarioInput
{
	std::string promptForScenarioName();
	std::vector<body::Body> createBodiesFromInput();
} // namespace ScenarioInput
