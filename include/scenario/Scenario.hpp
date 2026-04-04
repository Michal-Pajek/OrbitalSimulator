#pragma once
#include <string>
#include <vector>
#include "simulation/Body.hpp"

class Scenario
{
public:
	Scenario();
	double getDt() const { return m_dt; }
	unsigned int getSteps() const { return m_steps; }
	const std::string& getName() const { return m_name; }
	const std::vector<Body>& getBodies() const { return m_bodies; }
private:
	static std::vector<Body> createBodies();
	double m_dt{ 1.0 };
	unsigned int m_steps{ 1000u };		// temp value
	std::string m_name{};
	std::vector<Body> m_bodies{};
};