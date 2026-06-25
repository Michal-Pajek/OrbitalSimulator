#pragma once
#include <string>
#include <utility>
#include <vector>
#include "simulation/bodies/Body.hpp"

struct Scenario
{
	// Temporary constructor used only by Application::testScenario
	Scenario() : stepCount{ 1000u } {}
	Scenario(double timeStep, unsigned int stepCount, std::string name, std::vector<Body> bodies)
		: timeStep{ timeStep }, stepCount{ stepCount }, name{ std::move(name) }, bodies{ std::move(bodies) } {}
	double timeStep{ 1.0 };
	unsigned int stepCount;
	std::string name{};
	std::vector<Body> bodies{};
};
