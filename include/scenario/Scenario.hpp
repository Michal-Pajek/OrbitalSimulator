#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <vector>
#include "app/ExceptionHandler.hpp"
#include "simulation/bodies/Body.hpp"

struct Scenario
{
	Scenario(std::string scenarioName, std::vector<Body> scenarioBodies)
		: name{ std::move(scenarioName) }, bodies{ std::move(scenarioBodies) }
	{
		ExceptionHandler::ensure(!name.empty(),						ExceptionHandler::ExceptionType::Argument, "Scenario name must not be empty");
		ExceptionHandler::ensure(!bodies.empty(),					ExceptionHandler::ExceptionType::Argument, "Scenario must have at least one body");
		ExceptionHandler::ensure(bodies.size() <= MAX_BODY_COUNT,	ExceptionHandler::ExceptionType::Argument, "Scenario cannot contain more than the maximum number of bodies");
	}

	static constexpr std::size_t MAX_BODY_COUNT{ 20u };

	std::string name{};
	std::vector<Body> bodies{};
};
