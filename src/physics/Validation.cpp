#include "physics/Validation.hpp"

#include <cmath>

#include "physics/Constants.hpp"

namespace physics
{
	bool isSubLightVelocity(const double x, const double y, const double z)
	{
		const auto speed{ std::hypot(x, y, z) };
		return std::isfinite(speed) && speed < C_CONST;
	}

	bool isSubLightVelocity(const Vector3D& vec)
	{
		return isSubLightVelocity(vec.getX(), vec.getY(), vec.getZ());
	}
} // namespace physics
