#include "simulation/Simulation.hpp"

void Simulation::BodyStepState::applyStep()
{
	m_body.setPosition(m_newPos);
	m_body.setVelocity(m_newVel);
}

void Simulation::BodyStepState::calculateNextPosition(const double dt)
{
	const auto& position{ m_body.getPosition() };
	const auto& velocity{ m_body.getVelocity() };
	m_newPos = position + velocity * dt + 0.5 * m_acceleration * dt * dt;
	m_newVel = velocity + m_acceleration * dt;
}