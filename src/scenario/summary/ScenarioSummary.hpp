#pragma once
#include <span>
#include <string_view>

#include "body/Body.hpp"

struct Scenario;

namespace ScenarioSummary
{
	void print(std::string_view name, std::span<const body::Body> bodies);
	void print(const Scenario& scenario);
} // namespace ScenarioSummary
