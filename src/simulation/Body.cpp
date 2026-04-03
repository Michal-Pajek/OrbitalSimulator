#include "simulation/Body.hpp"
#include <stdexcept>
#include "physics/Constants.hpp"

Body::Body(const std::string& name, double mass, const Vector3D& pos, const Vector3D& vel) : m_name{ name }, m_mass{ mass }, m_position{ pos }, m_velocity{ vel }
{
	if (mass <= 0.0) {
		throw std::invalid_argument("Mass must be positive");
	}
}

Vector3D getGravityForceBetween(const Body& a, const Body& b)
{
	const auto positionDiff{ b.getPosition() - a.getPosition() };
	const auto distance{ positionDiff.getLength() };
	if (distance == 0.0) {
		throw std::domain_error("distance between two bodies is zero");
	}
	return physics::G_CONST * a.getMass() * b.getMass() * positionDiff / (distance * distance * distance);
}