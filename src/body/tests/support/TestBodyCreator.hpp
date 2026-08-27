#pragma once
#include <string>

#include "body/Body.hpp"
#include "body/types/BodyType.hpp"

#include "math/Vector3D.hpp"

namespace body::tests
{
	double getProperMass(const BodyTypeId id);
	Body createTestBody(const double mass, const Vector3D& position = {}, const Vector3D& velocity = {}, const std::string& name = "TEST_BODY");
} // namespace body::tests
