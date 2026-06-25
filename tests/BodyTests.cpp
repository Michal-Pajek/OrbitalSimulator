#include <cstddef>
#include <gtest/gtest.h>
#include <stdexcept>
#include "math/Vector3D.hpp"
#include "physics/Constants.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/types/BodyType.hpp"

constexpr double EPSILON{ 1e-12 };
constexpr BodyTypeId TEST_BODY_TYPE{ BodyTypeId::Asteroid };

TEST(GravityForceTests, CorrectDirectionHorizontal)
{
	const Body A{ "A", TEST_BODY_TYPE, 10.0, Vector3D{}, Vector3D{} };
	const Body B{ "B", TEST_BODY_TYPE, 12.0, Vector3D{10.0, 0.0, 0.0}, Vector3D{} };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_GT(force.getX(), 0.0);
	EXPECT_NEAR(force.getY(), 0.0, EPSILON);
}

TEST(GravityForceTests, CorrectDirectionVertical)
{
	const Body A{ "A", TEST_BODY_TYPE, 10.0, Vector3D{}, Vector3D{} };
	const Body B{ "B", TEST_BODY_TYPE, 12.0, Vector3D{0.0, 10.0, 0.0}, Vector3D{} };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_NEAR(force.getX(), 0.0, EPSILON);
	EXPECT_GT(force.getY(), 0.0);
	EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
}

TEST(GravityForceTests, ForceValueCalculationWorksCorrectly)
{
	const Body A{ "A", TEST_BODY_TYPE, 2.0, Vector3D{}, Vector3D{} };
	const Body B{ "B", TEST_BODY_TYPE, 3.0, Vector3D{2.0, 0.0, 0.0}, Vector3D{} };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_NEAR(force.getX(), 1.5 * physics::G_CONST, EPSILON);
	EXPECT_NEAR(force.getY(), 0.0, EPSILON);
	EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
}

TEST(GravityForceTests, ObeysThirdNewtonianRule)
{
	const Body A{ "A", TEST_BODY_TYPE, 2.0, Vector3D{0.0, 10.0, 5.0}, Vector3D{} };
	const Body B{ "B", TEST_BODY_TYPE, 3.0, Vector3D{2.0, 0.0, 0.0}, Vector3D{} };
	const auto forceAB{ getGravityForceBetween(A, B) };
	const auto forceBA{ getGravityForceBetween(B, A) };
	EXPECT_NEAR(forceAB.getX(), -forceBA.getX(), EPSILON);
	EXPECT_NEAR(forceAB.getY(), -forceBA.getY(), EPSILON);
	EXPECT_NEAR(forceAB.getZ(), -forceBA.getZ(), EPSILON);
}

TEST(BodyTests, ConstructorStoresBodyTypeId)
{
	for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
		const auto bodyTypeId{ static_cast<BodyTypeId>(id) };
		const Body body{ "A", bodyTypeId, 1.0, Vector3D{}, Vector3D{} };
		EXPECT_EQ(body.getTypeId(), bodyTypeId);
	}
}

TEST(BodyTests, SetTypeIdChangesBodyTypeId)
{
	for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
		Body body{ "A", static_cast<BodyTypeId>(id), 1.0, Vector3D{}, Vector3D{} };
		for (std::size_t newId{}; newId < BODY_TYPE_COUNT; ++newId) {
			const auto bodyTypeId{ static_cast<BodyTypeId>(newId) };
			body.setTypeId(bodyTypeId);
			EXPECT_EQ(body.getTypeId(), bodyTypeId);
		}
	}
}

TEST(BodyTests, ConstructorThrowsForInvalidBodyTypeId)
{
	EXPECT_THROW((Body{ "A", static_cast<BodyTypeId>(BODY_TYPE_COUNT), 1.0, Vector3D{}, Vector3D{} }), std::invalid_argument);
}

TEST(BodyTests, SetTypeIdThrowsForInvalidBodyTypeId)
{
	for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
		Body body{ "A", static_cast<BodyTypeId>(id), 1.0, Vector3D{}, Vector3D{} };
		EXPECT_THROW(body.setTypeId(static_cast<BodyTypeId>(BODY_TYPE_COUNT)), std::invalid_argument);
	}
}

TEST(BodyTests, ConstructorThrowsForNonPositiveMass)
{
	EXPECT_THROW((Body{ "A", TEST_BODY_TYPE, 0.0, Vector3D{}, Vector3D{} }), std::invalid_argument);
	EXPECT_THROW((Body{ "A", TEST_BODY_TYPE, -1.0, Vector3D{}, Vector3D{} }), std::invalid_argument);
}

TEST(BodyTests, SetMassThrowsForNonPositiveMass)
{
	Body body{ "A", TEST_BODY_TYPE, 1.0, Vector3D{}, Vector3D{} };
	EXPECT_THROW(body.setMass(0.0), std::invalid_argument);
	EXPECT_THROW(body.setMass(-1.0), std::invalid_argument);
}
