#pragma once
#include <vector>
#include "simulation/Body.hpp"

class Simulation
{
public:
	Simulation();
	void run();
private:
	void applyStepForAllBodies();
	void calculateNextStates(const double dt);
	void calculateForcesBetweenBodies();
	void resetForceForAllBodies();
	void step(const double dt);
	std::vector<Body> bodies;
};