#include "simulation/Simulation.hpp"
#include <stdexcept>

Simulation::Simulation(const std::vector<Body>& bodies)
{
	setBodies(bodies);
}

Simulation::Simulation(const std::vector<Body>& bodies, const double dt) : m_dt{ dt }
{
	if (dt <= 0.0) {
		throw std::invalid_argument("dt must be positive");
	}
	setBodies(bodies);
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
	m_bodyStepStates.clear();
	m_bodyStepStates.reserve(bodies.size());
	for (const auto& body : bodies) {
		m_bodyStepStates.emplace_back(body);
	}
	m_time = {};
}

void Simulation::setDt(const double dt)
{
	if (dt <= 0.0) {
		throw std::invalid_argument("dt must be positive");
	}
	m_dt = dt;
}

const Body& Simulation::getBody(const size_t idx) const
{
	if (idx >= m_bodyStepStates.size()) {
		throw std::out_of_range("idx is out of m_bodyStepStates range");
	}
	return m_bodyStepStates[idx].getBody();
}

void Simulation::applyStepForAllBodies()
{
	for (auto& x : m_bodyStepStates) {
		x.applyStep();
	}
}

void Simulation::calculateForcesBetweenBodies()
{
	const auto n{ m_bodyStepStates.size() };
	for (size_t i{}; i < n; ++i) {
		auto& stepStateA{ m_bodyStepStates[i] };
		for (size_t j{ i + 1 }; j < n; ++j) {
			auto& stepStateB{ m_bodyStepStates[j] };
			const auto forceVec{ getGravityForceBetween(stepStateA.getBody(), stepStateB.getBody())};
			stepStateA.increaseGravityForce(forceVec);
			stepStateB.increaseGravityForce(-forceVec);
		}
	}
}

void Simulation::calculateNextStates()
{
	for (auto& x : m_bodyStepStates) {
		x.calculateAcceleration();
		x.calculateNextPosition(m_dt);
	}
}

void Simulation::resetForceForAllBodies()
{
	for (auto& x : m_bodyStepStates) {
		x.resetForce();
	}
}
