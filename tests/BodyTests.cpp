#include <cmath>
#include <cstddef>
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include "math/Vector3D.hpp"
#include "physics/Constants.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/types/BodyType.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"
#include "support/TestBodyCreator.hpp"

using TestBodyCreator::createTestBody;
using TestBodyCreator::getProperMass;

constexpr double EPSILON{ 1e-12 };

TEST(GravityForceTests, CorrectDirectionHorizontal)
{
	const auto A{ createTestBody(10.0) };
	const auto B{ createTestBody(12.0, Vector3D{10.0, 0.0, 0.0}) };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_GT(force.getX(), 0.0);
	EXPECT_NEAR(force.getY(), 0.0, EPSILON);
}

TEST(GravityForceTests, CorrectDirectionVertical)
{
	const auto A{ createTestBody(10.0) };
	const auto B{ createTestBody(12.0, Vector3D{0.0, 10.0, 0.0}) };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_NEAR(force.getX(), 0.0, EPSILON);
	EXPECT_GT(force.getY(), 0.0);
	EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
}

TEST(GravityForceTests, ForceValueCalculationWorksCorrectly)
{
	const auto A{ createTestBody(2.0) };
	const auto B{ createTestBody(3.0, Vector3D{2.0, 0.0, 0.0}) };
	const auto force{ getGravityForceBetween(A, B) };
	EXPECT_NEAR(force.getX(), 1.5 * physics::G_CONST, EPSILON);
	EXPECT_NEAR(force.getY(), 0.0, EPSILON);
	EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
}

TEST(GravityForceTests, ObeysThirdNewtonianRule)
{
	const auto A{ createTestBody(2.0, Vector3D{0.0, 10.0, 5.0}) };
	const auto B{ createTestBody(3.0, Vector3D{2.0, 0.0, 0.0}) };
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
		const Body body{ "A", bodyTypeId, getProperMass(bodyTypeId), Vector3D{}, Vector3D{} };
		EXPECT_EQ(body.getTypeId(), bodyTypeId);
	}
}

TEST(BodyTests, ConstructorThrowsForInvalidBodyTypeId)
{
	EXPECT_THROW((Body{ "A", static_cast<BodyTypeId>(BODY_TYPE_COUNT), 1.0, Vector3D{}, Vector3D{} }), std::invalid_argument);
}

TEST(BodyTests, ConstructorThrowsForNonPositiveMass)
{
	EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, 0.0, Vector3D{}, Vector3D{} }), std::invalid_argument);
	EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, -1.0, Vector3D{}, Vector3D{} }), std::invalid_argument);
}

TEST(BodyTests, SetMassThrowsForNonPositiveMass)
{
	auto body{ createTestBody(1.0) };
	EXPECT_THROW(body.setMass(0.0), std::invalid_argument);
	EXPECT_THROW(body.setMass(-1.0), std::invalid_argument);
}

TEST(BodyTests, SetTypeAndMassChangesBothValues)
{
	auto body{ createTestBody(1.0) };

	for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
		const auto newTypeId{ static_cast<BodyTypeId>(id) };
		const auto newMass{ getProperMass(newTypeId) };

		body.setTypeAndMass(newTypeId, newMass);

		EXPECT_EQ(body.getTypeId(), newTypeId);
		EXPECT_DOUBLE_EQ(body.getMass(), newMass);
	}
}

TEST(BodyTests, SetTypeAndMassThrowsForInvalidBodyTypeId)
{
	auto body{ createTestBody(1.0) };
	EXPECT_THROW(body.setTypeAndMass(static_cast<BodyTypeId>(BODY_TYPE_COUNT), 1.0), std::invalid_argument);
}

TEST(BodyTests, SetTypeAndMassThrowsForMismatchedMassAndPreservesState)
{
	auto body{ createTestBody(1.0) };
	for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
		const auto initialTypeId{ body.getTypeId() };
		const auto initialMass{ body.getMass() };
		const auto newTypeId{ static_cast<BodyTypeId>(id) };
		const auto massInterval{ BodyTypeCatalog::getType(newTypeId).getMassInterval() };
		const auto massTooLow{ std::nextafter(massInterval.min, 0.0) };
		const auto massTooHigh{ std::nextafter(massInterval.max, std::numeric_limits<double>::infinity()) };

		EXPECT_THROW(body.setTypeAndMass(newTypeId, massTooLow), std::invalid_argument);
		EXPECT_EQ(body.getTypeId(), initialTypeId);
		EXPECT_DOUBLE_EQ(body.getMass(), initialMass);

		EXPECT_THROW(body.setTypeAndMass(newTypeId, massTooHigh), std::invalid_argument);
		EXPECT_EQ(body.getTypeId(), initialTypeId);
		EXPECT_DOUBLE_EQ(body.getMass(), initialMass);
	}
}
