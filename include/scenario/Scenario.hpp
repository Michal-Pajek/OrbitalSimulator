#pragma once
#include <string>
#include <utility>
#include <vector>
#include "simulation/bodies/Body.hpp"

struct Scenario
{
	Scenario() = default;		// temp version
	Scenario(double timeStep, unsigned int stepCount, std::string name, std::vector<Body> bodies) : timeStep{ timeStep }, stepCount{ stepCount }, name{ std::move(name) }, bodies{ std::move(bodies) } {}
	double timeStep{ 1.0 };
	unsigned int stepCount{ 1000u };		// temp value
	std::string name{};
	std::vector<Body> bodies{};
};