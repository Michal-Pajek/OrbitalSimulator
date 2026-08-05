#pragma once
#include <cstddef>
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
		if (bodies.size() > MAX_BODY_COUNT) {
			throw std::invalid_argument{ "Scenario cannot contain more than the maximum number of bodies" };
		}
	}

	static constexpr std::size_t MAX_BODY_COUNT{ 20u };

	std::string name{};
	std::vector<Body> bodies{};
};
