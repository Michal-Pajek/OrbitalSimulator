#include <gtest/gtest.h>
#include "math/Vector2D.hpp"
#include "physics/Constants.hpp"
#include "simulation/Body.hpp"

constexpr double EPSILON{ 1e-12 };

TEST(GravityForceTests, CorrectDirectionHorizontal)
{
	const Body A{ "A", 10.0, Vector2D{}, Vector2D{} };
	const Body B{ "B", 12.0, Vector2D{10.0, 0.0}, Vector2D{} };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_GT(force.getX(), 0.0);
	EXPECT_NEAR(force.getY(), 0.0, EPSILON);
}

TEST(GravityForceTests, CorrectDirectionVertical)
{
	const Body A{ "A", 10.0, Vector2D{}, Vector2D{} };
	const Body B{ "B", 12.0, Vector2D{0.0, 10.0}, Vector2D{} };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_NEAR(force.getX(), 0.0, EPSILON);
	EXPECT_GT(force.getY(), 0.0);
}

TEST(GravityForceTests, ForceValueCalculationWorksCorrectly)
{
	const Body A{ "A", 2.0, Vector2D{}, Vector2D{} };
	const Body B{ "B", 3.0, Vector2D{2.0, 0.0}, Vector2D{} };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_NEAR(force.getX(), 1.5 * physics::G_CONST, EPSILON);
	EXPECT_NEAR(force.getY(), 0.0, EPSILON);
}

TEST(GravityForceTests, ObeysThirdNewtonianRule)
{
	const Body A{ "A", 2.0, Vector2D{0.0, 10.0}, Vector2D{} };
	const Body B{ "B", 3.0, Vector2D{2.0, 0.0}, Vector2D{} };
	const auto forceAB{ getGravityForceBetween(A, B) };
	const auto forceBA{ getGravityForceBetween(B, A) };
	EXPECT_NEAR(forceAB.getX(), -forceBA.getX(), EPSILON);
	EXPECT_NEAR(forceAB.getY(), -forceBA.getY(), EPSILON);
}