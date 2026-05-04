#pragma once
#include <string>
#include <utility>
#include <vector>
#include "simulation/bodies/Body.hpp"

struct Scenario
{
	Scenario() = default;		// temp version
	Scenario(double timeStep, unsigned int stepCount, std::string name, std::vector<Body> bodies) : m_timeStep{ timeStep }, m_stepCount{ stepCount }, m_name{ std::move(name) }, m_bodies{ std::move(bodies) } {}
	double m_timeStep{ 1.0 };
	unsigned int m_stepCount{ 1000u };		// temp value
	std::string m_name{};
	std::vector<Body> m_bodies{};
};