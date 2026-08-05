#pragma once
#include <span>
#include <string_view>
#include "simulation/bodies/Body.hpp"

struct Scenario;

namespace ScenarioSummary
{
	void print(std::string_view name, std::span<const Body> bodies);
	void print(const Scenario& scenario);
}
