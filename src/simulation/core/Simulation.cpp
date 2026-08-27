#include "simulation/core/Simulation.hpp"

#include "common/runtime_checks/RuntimeChecks.hpp"

Simulation::Simulation(const std::vector<body::Body>& bodies)
{
	setBodies(bodies);
}

Simulation::Simulation(const std::vector<body::Body>& bodies, const double dt) : m_dt{ dt }
{
	runtime_checks::ensure(dt > 0.0, runtime_checks::Type::Argument, "dt must be positive");
	setBodies(bodies);
}

void Simulation::runSteps(const unsigned int n)
{
	for (unsigned int i{}; i < n; ++i) {
		step();
	}
}

void Simulation::step()
{
	runtime_checks::ensure(!m_bodyStepStates.empty(), runtime_checks::Type::Logic, "Cannot perform simulation step: no bodies in simulation");
	resetForceForAllBodies();
	calculateForcesBetweenBodies();
	calculateNextStates();
	applyStepForAllBodies();
	m_time += m_dt;
}

void Simulation::setBodies(const std::vector<body::Body>& bodies)
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
	runtime_checks::ensure(dt > 0.0, runtime_checks::Type::Argument, "dt must be positive");
	m_dt = dt;
}

const body::Body& Simulation::getBody(const size_t idx) const
{
	runtime_checks::ensure(idx < m_bodyStepStates.size(), runtime_checks::Type::Range, "idx is out of m_bodyStepStates range");
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
