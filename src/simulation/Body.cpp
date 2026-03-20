#include "simulation/Body.hpp"
#include <iostream>
#include <cmath>
#include "physics/Constants.hpp"

void Body::calculateNextPosition(const double dt)
{
	m_newPos = m_position + m_velocity * dt + 0.5 * m_acceleration * dt * dt;
	m_newVel = m_velocity + m_acceleration * dt;
}

void Body::applyStep()
{
	m_position = m_newPos;
	m_velocity = m_newVel;
}

void Body::debugPrint() const
{
	std::cout << m_name << " (mass " << m_mass << "kg):\n";
	std::cout << "\tgravity force: " << m_force << '\n';
	std::cout << "\tposition: " << m_position << '\n';
	std::cout << "\tvelocity: " << m_velocity << '\n';
	std::cout << "\tacceleration: " << m_acceleration << '\n';
}

Vector2D getGravityForceBetween(const Body& a, const Body& b)
{
	const auto positionDiff{ b.getPosition() - a.getPosition() };
	const auto distance{ positionDiff.getLength() };
	return physics::G_CONST * a.getMass() * b.getMass() * positionDiff / pow(distance, 3.0);
}
