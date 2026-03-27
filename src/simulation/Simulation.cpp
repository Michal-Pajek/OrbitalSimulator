#include "simulation/Simulation.hpp"
#include <stdexcept>
#include <utility>

Simulation::Simulation(const std::vector<Body>& bodies, const double dt) : m_bodies{ bodies }, m_dt{ dt }
{
	if (dt <= 0.0) {
		throw std::invalid_argument("dt must be positive");
	}
}

void Simulation::step()
{
	resetForceForAllBodies();
	calculateForcesBetweenBodies();
	calculateNextStates();
	applyStepForAllBodies();
	m_time += m_dt;
}

void Simulation::setBodies(const std::vector<Body>& bodies)
{
	m_bodies = bodies;
	m_time = {};
}

void Simulation::setBodies(std::vector<Body>&& bodies)
{
	m_bodies = std::move(bodies);
	m_time = {};
}

void Simulation::setDt(const double dt)
{
	if (dt <= 0.0) {
		throw std::invalid_argument("dt must be positive");
	}
	m_dt = dt;
}

void Simulation::applyStepForAllBodies()
{
	for (auto& x : m_bodies) {
		x.applyStep();
	}
}

void Simulation::calculateForcesBetweenBodies()
{
	const auto n{ m_bodies.size() };
	for (size_t i{}; i < n; ++i) {
		for (size_t j{ i + 1 }; j < n; ++j) {
			const auto forceVec{ getGravityForceBetween(m_bodies[i], m_bodies[j]) };
			m_bodies[i].increaseGravityForce(forceVec);
			m_bodies[j].increaseGravityForce(-forceVec);
		}
	}
}

void Simulation::calculateNextStates()
{
	for (auto& x : m_bodies) {
		x.calculateAcceleration();
		x.calculateNextPosition(m_dt);
	}
}

void Simulation::resetForceForAllBodies()
{
	for (auto& x : m_bodies) {
		x.resetForce();
	}
}
