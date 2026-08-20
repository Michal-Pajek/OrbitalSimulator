#include "simulation/bodies/Body.hpp"

#include <cmath>
#include <cstddef>

#include "simulation/bodies/types/BodyTypeCatalog.hpp"

#include "common/RuntimeChecks.hpp"
#include "localization/TextId.hpp"
#include "physics/Constants.hpp"
#include "physics/Validation.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	void validateMass(const double mass, const BodyTypeId typeId)
	{
		RuntimeChecks::ensure(mass > 0.0,									RuntimeChecks::Type::Argument, "Mass must be positive");
		RuntimeChecks::ensure(std::isfinite(mass),							RuntimeChecks::Type::Argument, "Mass must be finite");
		RuntimeChecks::ensure(BodyTypeCatalog::isMassInRange(typeId, mass),	RuntimeChecks::Type::Argument, "Mass is out of interval for the specified type");
	}

	void validateTypeId(const BodyTypeId bodyTypeId)
	{
		RuntimeChecks::ensure(static_cast<std::size_t>(bodyTypeId) < BODY_TYPE_COUNT, RuntimeChecks::Type::Argument, "typeId out of range");
	}

	void validateVelocityVector(const Vector3D& velocity)
	{
		RuntimeChecks::ensure(physics::isSubLightVelocity(velocity), RuntimeChecks::Type::Argument, "Velocity must be lower than c");
	}
} // anonymous namespace

Body::Body(const std::string& name, BodyTypeId typeId, double mass, const Vector3D& position, const Vector3D& velocity)
	: m_name{name}, m_typeId{typeId}, m_mass{mass}, m_position{position}, m_velocity{velocity}
{
	validateTypeId(typeId);
	validateMass(mass, typeId);
	validateVelocityVector(velocity);
}

void Body::printSummary(const bool oneLine) const
{
	const auto sep{ oneLine ? '\t' : '\n' };
	ConsoleWriter::writeLine(m_name, " (", BodyTypeCatalog::getType(m_typeId).getTextId(), ')', sep, TextId::Mass, " (kg): ", m_mass, sep, TextId::Position, " (m): ", m_position, sep, TextId::Velocity, " (m/s): ", m_velocity);
}

void Body::setMass(const double mass)
{
	validateMass(mass, m_typeId);
	m_mass = mass;
}

void Body::setTypeAndMass(const BodyTypeId typeId, const double mass)
{
	validateTypeId(typeId);
	validateMass(mass, typeId);

	m_typeId = typeId;
	m_mass = mass;
}

void Body::setVelocity(const Vector3D& velocity)
{
	validateVelocityVector(velocity);
	m_velocity = velocity;
}

Vector3D getGravityForceBetween(const Body& a, const Body& b)
{
	const auto positionDiff{ b.getPosition() - a.getPosition() };
	const auto distance{ positionDiff.getLength() };
	RuntimeChecks::ensure(distance > 0.0, RuntimeChecks::Type::Domain, "Distance between two bodies is zero");
	return physics::G_CONST * a.getMass() * b.getMass() * positionDiff / (distance * distance * distance);
}
