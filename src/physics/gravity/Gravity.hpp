#pragma once
#include "math/Vector3D.hpp"

namespace body
{
	class Body;
} // namespace body

namespace physics
{
	math::Vector3D getGravityForceBetween(const body::Body& a, const body::Body& b);
} // namespace physics
