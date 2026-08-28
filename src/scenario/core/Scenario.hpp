#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "body/Body.hpp"
#include "common/runtime_checks/RuntimeChecks.hpp"

namespace scenario
{
	struct Scenario
	{
		Scenario(std::string scenarioName, std::vector<body::Body> scenarioBodies)
			: name{ std::move(scenarioName) }, bodies{ std::move(scenarioBodies) }
		{
			runtime_checks::ensure(!name.empty(), runtime_checks::Type::Argument, "Scenario name must not be empty");
			runtime_checks::ensure(!bodies.empty(), runtime_checks::Type::Argument, "Scenario must have at least one body");
			runtime_checks::ensure(bodies.size() <= MAX_BODY_COUNT, runtime_checks::Type::Argument, "Scenario cannot contain more than the maximum number of bodies");
		}

		static constexpr std::size_t MAX_BODY_COUNT{ 20u };

		std::string name{};
		std::vector<body::Body> bodies{};
	};
} // namespace scenario
