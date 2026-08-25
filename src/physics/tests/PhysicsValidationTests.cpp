#include <cmath>
#include <gtest/gtest.h>
#include <limits>

#include "physics/Constants.hpp"
#include "physics/Validation.hpp"

#include "math/Vector3D.hpp"

TEST(PhysicsValidationTests, AcceptsZeroVelocity)
{
	EXPECT_TRUE(physics::isSubLightVelocity(0.0, 0.0, 0.0));
}

TEST(PhysicsValidationTests, AcceptsVelocityBelowSpeedOfLight)
{
	const auto velocity{ std::nextafter(physics::C_CONST, 0.0) };

	EXPECT_TRUE(physics::isSubLightVelocity(velocity, 0.0, 0.0));
}

TEST(PhysicsValidationTests, RejectsVelocityEqualToSpeedOfLight)
{
	EXPECT_FALSE(physics::isSubLightVelocity(physics::C_CONST, 0.0, 0.0));
}

TEST(PhysicsValidationTests, RejectsVelocityAboveSpeedOfLight)
{
	const auto velocity{ std::nextafter(physics::C_CONST, std::numeric_limits<double>::infinity()) };

	EXPECT_FALSE(physics::isSubLightVelocity(velocity, 0.0, 0.0));
}

TEST(PhysicsValidationTests, ValidatesLengthOfVelocityVector)
{
	constexpr auto component{ 0.8 * physics::C_CONST };

	EXPECT_FALSE(physics::isSubLightVelocity(component, component, 0.0));
}

TEST(PhysicsValidationTests, SupportsNegativeComponents)
{
	EXPECT_TRUE(physics::isSubLightVelocity(-0.5 * physics::C_CONST, 0.0, 0.0));
}

TEST(PhysicsValidationTests, RejectsNonFiniteComponents)
{
	constexpr auto infinity{ std::numeric_limits<double>::infinity() };
	constexpr auto nan{ std::numeric_limits<double>::quiet_NaN() };

	EXPECT_FALSE(physics::isSubLightVelocity(infinity, 0.0, 0.0));
	EXPECT_FALSE(physics::isSubLightVelocity(nan, 0.0, 0.0));
}

TEST(PhysicsValidationTests, VectorOverloadUsesVectorLength)
{
	constexpr auto component{ 0.8 * physics::C_CONST };
	const Vector3D velocity{ component, component, 0.0 };

	EXPECT_FALSE(physics::isSubLightVelocity(velocity));
}
