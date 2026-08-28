#pragma once
#include "math/Vector3D.hpp"

namespace physics
{
	bool isSubLightVelocity(const double x, const double y, const double z);
	bool isSubLightVelocity(const math::Vector3D& vec);
} // namespace physics
