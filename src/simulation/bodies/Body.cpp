#include "simulation/bodies/Body.hpp"
#include <stdexcept>
#include "localization/TextId.hpp"
#include "physics/Constants.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	void validateMass(const double mass)
	{
		if (mass <= 0.0) {
			throw std::invalid_argument("Mass must be positive");
		}
	}

	void validateTypeId(const BodyTypeId bodyTypeId)
	{
		if (static_cast<std::size_t>(bodyTypeId) >= BODY_TYPE_COUNT) {
			throw std::invalid_argument("typeId out of range");
		}
	}
} // anonymous namespace

Body::Body(const std::string& name, BodyTypeId typeId, double mass, const Vector3D& position, const Vector3D& velocity) : m_name{name}, m_typeId{typeId}, m_mass{mass}, m_position{position}, m_velocity{velocity}
{
	validateMass(mass);
	validateTypeId(typeId);
}

void Body::printSummary(const bool oneLine) const
{
	const auto sep{ oneLine ? '\t' : '\n' };
	ConsoleWriter::writeLine(m_name, " (", BodyTypeCatalog::getType(m_typeId).getTextId(), ')', sep, TextId::Mass, " (kg): ", m_mass, sep, TextId::Position, " (m): ", m_position, sep, TextId::Velocity, " (m/s): ", m_velocity);
}

void Body::setMass(const double mass)
{
	validateMass(mass);
	m_mass = mass;
}

void Body::setTypeId(const BodyTypeId bodyTypeId)
{
	validateTypeId(bodyTypeId);
	m_typeId = bodyTypeId;
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