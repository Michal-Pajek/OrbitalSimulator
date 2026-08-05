#pragma once
#include <string>
#include "math/Vector3D.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/types/BodyType.hpp"

namespace TestBodyCreator
{
	double getProperMass(const BodyTypeId id);
	Body createTestBody(const double mass, const Vector3D& position = {}, const Vector3D& velocity = {}, const std::string& name = "TEST_BODY");
}
