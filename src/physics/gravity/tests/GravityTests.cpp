#include <gtest/gtest.h>

#include "physics/Constants.hpp"
#include "physics/gravity/Gravity.hpp"

#include "body/tests/support/TestBodyCreator.hpp"

namespace physics::tests
{
	namespace
	{
		constexpr double EPSILON{ 1e-12 };
	} // anonymous namespace

	TEST(GravityForceTests, CorrectDirectionHorizontal)
	{
		const auto A{ body::tests::createTestBody(10.0) };
		const auto B{ body::tests::createTestBody(12.0, math::Vector3D{10.0, 0.0, 0.0}) };
		const auto force{ getGravityForceBetween(A, B) };
		EXPECT_GT(force.getX(), 0.0);
		EXPECT_NEAR(force.getY(), 0.0, EPSILON);
	}

	TEST(GravityForceTests, CorrectDirectionVertical)
	{
		const auto A{ body::tests::createTestBody(10.0) };
		const auto B{ body::tests::createTestBody(12.0, math::Vector3D{0.0, 10.0, 0.0}) };
		const auto force{ getGravityForceBetween(A, B) };
		EXPECT_NEAR(force.getX(), 0.0, EPSILON);
		EXPECT_GT(force.getY(), 0.0);
		EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
	}

	TEST(GravityForceTests, ForceValueCalculationWorksCorrectly)
	{
		const auto A{ body::tests::createTestBody(2.0) };
		const auto B{ body::tests::createTestBody(3.0, math::Vector3D{2.0, 0.0, 0.0}) };
		const auto force{ getGravityForceBetween(A, B) };
		EXPECT_NEAR(force.getX(), 1.5 * G_CONST, EPSILON);
		EXPECT_NEAR(force.getY(), 0.0, EPSILON);
		EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
	}

	TEST(GravityForceTests, ObeysThirdNewtonianRule)
	{
		const auto A{ body::tests::createTestBody(2.0, math::Vector3D{0.0, 10.0, 5.0}) };
		const auto B{ body::tests::createTestBody(3.0, math::Vector3D{2.0, 0.0, 0.0}) };
		const auto forceAB{ getGravityForceBetween(A, B) };
		const auto forceBA{ getGravityForceBetween(B, A) };
		EXPECT_NEAR(forceAB.getX(), -forceBA.getX(), EPSILON);
		EXPECT_NEAR(forceAB.getY(), -forceBA.getY(), EPSILON);
		EXPECT_NEAR(forceAB.getZ(), -forceBA.getZ(), EPSILON);
	}
} // namespace physics::tests
