#pragma once
#include <string>
#include <vector>

#include "body/Body.hpp"

namespace scenario::input
{
	std::string promptForScenarioName();
	std::vector<body::Body> createBodiesFromInput();
} // namespace scenario::input
