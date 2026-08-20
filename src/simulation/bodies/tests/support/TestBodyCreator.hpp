#pragma once
#include <string>

#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/types/BodyType.hpp"

#include "math/Vector3D.hpp"

namespace TestBodyCreator
{
	double getProperMass(const BodyTypeId id);
	Body createTestBody(const double mass, const Vector3D& position = {}, const Vector3D& velocity = {}, const std::string& name = "TEST_BODY");
} // namespace TestBodyCreator
