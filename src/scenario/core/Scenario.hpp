#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "common/RuntimeChecks.hpp"
#include "bodies/Body.hpp"

struct Scenario
{
	Scenario(std::string scenarioName, std::vector<Body> scenarioBodies)
		: name{ std::move(scenarioName) }, bodies{ std::move(scenarioBodies) }
	{
		RuntimeChecks::ensure(!name.empty(),					RuntimeChecks::Type::Argument, "Scenario name must not be empty");
		RuntimeChecks::ensure(!bodies.empty(),					RuntimeChecks::Type::Argument, "Scenario must have at least one body");
		RuntimeChecks::ensure(bodies.size() <= MAX_BODY_COUNT,	RuntimeChecks::Type::Argument, "Scenario cannot contain more than the maximum number of bodies");
	}

	static constexpr std::size_t MAX_BODY_COUNT{ 20u };

	std::string name{};
	std::vector<Body> bodies{};
};
