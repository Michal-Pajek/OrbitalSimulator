#include "simulation/Simulation.hpp"
#include <iostream>

Simulation::Simulation()
{
	bodies.emplace_back("A", 1E15, Vector2D{ 0.0, 0.0 }, Vector2D{2.0, 0.0});
	bodies.emplace_back("B", 5E14, Vector2D{ 100.0, 150.0 }, Vector2D{0.0, 10.0});
}

void Simulation::run()
{
	constexpr double DT{ 1.0 };	//s
	constexpr unsigned int STEPS{ 200 };

	std::cout << "TEST SIMULATION START\n";
	
	for (unsigned int i{}; i < STEPS; ++i) {
		step(DT);
	}
}

void Simulation::applyStepForAllBodies()
{
	for (auto& x : bodies) {
		x.applyStep();
		x.debugPrint();
	}
}

void Simulation::calculateNextStates(const double dt)
{
	for (auto& x : bodies) {
		x.calculateAcceleration();
		x.calculateNextPosition(dt);
	}
}

void Simulation::calculateForcesBetweenBodies()
{
	const auto n{ bodies.size() };
	for (size_t i{}; i < n; ++i) {
		for (size_t j{ i + 1 }; j < n; ++j) {
			const auto forceVec{ getGravityForceBetween(bodies[i], bodies[j]) };
			bodies[i].increaseGravityForce(forceVec);
			bodies[j].increaseGravityForce(-forceVec);
		}
	}
}

void Simulation::resetForceForAllBodies()
{
	for (auto& x : bodies) {
		x.resetForce();
	}
}

void Simulation::step(const double dt)
{
	resetForceForAllBodies();
	calculateForcesBetweenBodies();
	calculateNextStates(dt);
	applyStepForAllBodies();
}
