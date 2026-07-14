#pragma once
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "simulation/bodies/Body.hpp"

struct Scenario
{
	Scenario(std::string scenarioName, std::vector<Body> scenarioBodies)
		: name{ std::move(scenarioName) }, bodies{ std::move(scenarioBodies) }
	{
		if (name.empty()) {
			throw std::invalid_argument{ "Scenario name must not be empty" };
		}
		if (bodies.empty()) {
			throw std::invalid_argument{ "Scenario must have at least one body" };
		}
	}

	std::string name{};
	std::vector<Body> bodies{};
};
