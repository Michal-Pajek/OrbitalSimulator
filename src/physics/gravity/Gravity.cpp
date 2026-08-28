#include "physics/gravity/Gravity.hpp"

#include "physics/Constants.hpp"

#include "body/Body.hpp"
#include "common/runtime_checks/RuntimeChecks.hpp"

namespace physics
{
	math::Vector3D getGravityForceBetween(const body::Body& a, const body::Body& b)
	{
		const auto positionDiff{ b.getPosition() - a.getPosition() };
		const auto distance{ positionDiff.getLength() };
		runtime_checks::ensure(distance > 0.0, runtime_checks::Type::Domain, "Distance between two bodies is zero");
		return G_CONST * a.getMass() * b.getMass() * positionDiff / (distance * distance * distance);
	}
} // namespace physics
