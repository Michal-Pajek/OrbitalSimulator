#include "body/Body.hpp"

#include <cmath>
#include <cstddef>

#include "body/types/BodyTypeCatalog.hpp"

#include "common/runtime_checks/RuntimeChecks.hpp"
#include "physics/Validation.hpp"

namespace body
{
	namespace
	{
		void validateMass(const double mass, const BodyTypeId typeId)
		{
			runtime_checks::ensure(mass > 0.0,										runtime_checks::Type::Argument, "Mass must be positive");
			runtime_checks::ensure(std::isfinite(mass),								runtime_checks::Type::Argument, "Mass must be finite");
			runtime_checks::ensure(BodyTypeCatalog::isMassInRange(typeId, mass),	runtime_checks::Type::Argument, "Mass is out of interval for the specified type");
		}

		void validateTypeId(const BodyTypeId bodyTypeId)
		{
			runtime_checks::ensure(static_cast<std::size_t>(bodyTypeId) < BODY_TYPE_COUNT, runtime_checks::Type::Argument, "typeId out of range");
		}

		void validateVelocityVector(const math::Vector3D& velocity)
		{
			runtime_checks::ensure(physics::isSubLightVelocity(velocity), runtime_checks::Type::Argument, "Velocity must be lower than c");
		}
	} // anonymous namespace

	Body::Body(const std::string& name, BodyTypeId typeId, double mass, const math::Vector3D& position, const math::Vector3D& velocity)
		: m_name{ name }, m_typeId{ typeId }, m_mass{ mass }, m_position{ position }, m_velocity{ velocity }
	{
		validateTypeId(typeId);
		validateMass(mass, typeId);
		validateVelocityVector(velocity);
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

	void Body::setVelocity(const math::Vector3D& velocity)
	{
		validateVelocityVector(velocity);
		m_velocity = velocity;
	}
} // namespace body
