#include "simulation/core/Simulation.hpp"

#include "common/runtime_checks/RuntimeChecks.hpp"
#include "physics/Validation.hpp"

void Simulation::BodyStepState::applyStep()
{
	m_body.setPosition(m_newPos);
	m_body.setVelocity(m_newVel);
}

void Simulation::BodyStepState::calculateNextPosition(const double dt)
{
	const auto& position{ m_body.getPosition() };
	const auto& velocity{ m_body.getVelocity() };
	const auto newPos{ position + velocity * dt + 0.5 * m_acceleration * dt * dt };
	const auto newVel{ velocity + m_acceleration * dt };

	RuntimeChecks::ensure(physics::isSubLightVelocity(newVel), RuntimeChecks::Type::Runtime, "Current velocity is not below the speed of light");

	m_newPos = newPos;
	m_newVel = newVel;
}
