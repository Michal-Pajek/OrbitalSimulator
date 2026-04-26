#pragma once
#include <string>
#include <utility>
#include <vector>
#include "simulation/Body.hpp"

class Scenario
{
public:
	Scenario();		// temp version
	Scenario(double timeStep, unsigned int stepCount, std::string name, std::vector<Body> bodies) : m_timeStep{ timeStep }, m_stepCount{ stepCount }, m_name{ std::move(name) }, m_bodies{ std::move(bodies) } {}
	double getTimeStep() const { return m_timeStep; }
	unsigned int getStepCount() const { return m_stepCount; }
	const std::string& getName() const { return m_name; }
	const std::vector<Body>& getBodies() const { return m_bodies; }
private:
	static std::vector<Body> createBodies();
	double m_timeStep{ 1.0 };
	unsigned int m_stepCount{ 1000u };		// temp value
	std::string m_name{};
	std::vector<Body> m_bodies{};
};