#pragma once
#include <vector>
#include "simulation/Body.hpp"

class Simulation
{
public:
	Simulation() = delete;
	Simulation(const std::vector<Body>& bodies) : m_bodies{ bodies } {}
	Simulation(const std::vector<Body>& bodies, const double dt);
	void step();
	void setBodies(const std::vector<Body>& bodies);
	void setBodies(std::vector<Body>&& bodies);
	void setDt(const double dt);
	double getDt() const { return m_dt; }
	double getTime() const { return m_time; }
	const std::vector<Body>& getBodies() const { return m_bodies; }
private:
	void applyStepForAllBodies();
	void calculateForcesBetweenBodies();
	void calculateNextStates();
	void resetForceForAllBodies();
	std::vector<Body> m_bodies;
	double m_dt{ 1.0 };
	double m_time{};
};