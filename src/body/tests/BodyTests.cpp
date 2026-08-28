#include <cmath>
#include <cstddef>
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>

#include "body/Body.hpp"
#include "body/tests/support/TestBodyCreator.hpp"
#include "body/types/BodyType.hpp"
#include "body/types/BodyTypeCatalog.hpp"

#include "math/Vector3D.hpp"
#include "physics/Constants.hpp"

namespace body::tests
{
	namespace
	{
		constexpr double EPSILON{ 1e-12 };
	} // anonymous namespace

	TEST(GravityForceTests, CorrectDirectionHorizontal)
	{
		const auto A{ createTestBody(10.0) };
		const auto B{ createTestBody(12.0, math::Vector3D{10.0, 0.0, 0.0}) };
		const auto force{ getGravityForceBetween(A, B) };
		EXPECT_GT(force.getX(), 0.0);
		EXPECT_NEAR(force.getY(), 0.0, EPSILON);
	}

	TEST(GravityForceTests, CorrectDirectionVertical)
	{
		const auto A{ createTestBody(10.0) };
		const auto B{ createTestBody(12.0, math::Vector3D{0.0, 10.0, 0.0}) };
		const auto force{ getGravityForceBetween(A, B) };
		EXPECT_NEAR(force.getX(), 0.0, EPSILON);
		EXPECT_GT(force.getY(), 0.0);
		EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
	}

	TEST(GravityForceTests, ForceValueCalculationWorksCorrectly)
	{
		const auto A{ createTestBody(2.0) };
		const auto B{ createTestBody(3.0, math::Vector3D{2.0, 0.0, 0.0}) };
		const auto force{ getGravityForceBetween(A, B) };
		EXPECT_NEAR(force.getX(), 1.5 * physics::G_CONST, EPSILON);
		EXPECT_NEAR(force.getY(), 0.0, EPSILON);
		EXPECT_NEAR(force.getZ(), 0.0, EPSILON);
	}

	TEST(GravityForceTests, ObeysThirdNewtonianRule)
	{
		const auto A{ createTestBody(2.0, math::Vector3D{0.0, 10.0, 5.0}) };
		const auto B{ createTestBody(3.0, math::Vector3D{2.0, 0.0, 0.0}) };
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
			const Body body{ "A", bodyTypeId, getProperMass(bodyTypeId), math::Vector3D{}, math::Vector3D{} };
			EXPECT_EQ(body.getTypeId(), bodyTypeId);
		}
	}

	TEST(BodyTests, ConstructorThrowsForInvalidBodyTypeId)
	{
		EXPECT_THROW((Body{ "A", static_cast<BodyTypeId>(BODY_TYPE_COUNT), 1.0, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
	}

	TEST(BodyTests, ConstructorThrowsForNonPositiveMass)
	{
		EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, 0.0, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
		EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, -1.0, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
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

	TEST(BodyTests, ConstructorThrowsForNonFiniteMass)
	{
		constexpr auto infinity{ std::numeric_limits<double>::infinity() };
		constexpr auto nan{ std::numeric_limits<double>::quiet_NaN() };

		EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, infinity, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
		EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, -infinity, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
		EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, nan, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
	}

	TEST(BodyTests, ConstructorThrowsForMassOutsideTypeInterval)
	{
		for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
			const auto bodyTypeId{ static_cast<BodyTypeId>(id) };
			const auto [min, max] { BodyTypeCatalog::getType(bodyTypeId).getMassInterval() };
			const auto massTooLow{ std::nextafter(min, 0.0) };
			const auto massTooHigh{ std::nextafter(max, std::numeric_limits<double>::infinity()) };

			SCOPED_TRACE(
				::testing::Message{}
				<< "Body type id: "
				<< id);

			EXPECT_THROW((Body{ "A", bodyTypeId, massTooLow, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
			EXPECT_THROW((Body{ "A", bodyTypeId, massTooHigh, math::Vector3D{}, math::Vector3D{} }), std::invalid_argument);
		}
	}

	TEST(BodyTests, SetMassThrowsForOutOfRangeMassAndPreservesState)
	{
		for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
			const auto bodyTypeId{ static_cast<BodyTypeId>(id) };
			const auto initialMass{ getProperMass(bodyTypeId) };
			const auto [min, max] { BodyTypeCatalog::getType(bodyTypeId).getMassInterval() };
			const auto massTooLow{ std::nextafter(min, 0.0) };
			const auto massTooHigh{ std::nextafter(max,std::numeric_limits<double>::infinity()) };

			Body body{ "A", bodyTypeId, initialMass, math::Vector3D{}, math::Vector3D{} };

			SCOPED_TRACE(
				::testing::Message{}
				<< "Body type id: "
				<< id);

			EXPECT_THROW(body.setMass(massTooLow), std::invalid_argument);
			EXPECT_DOUBLE_EQ(body.getMass(), initialMass);
			EXPECT_THROW(body.setMass(massTooHigh), std::invalid_argument);
			EXPECT_DOUBLE_EQ(body.getMass(), initialMass);
		}
	}

	TEST(BodyTests, SetMassThrowsForNonFiniteMassAndPreservesState)
	{
		auto body{ createTestBody(1.0) };
		const auto initialMass{ body.getMass() };
		constexpr auto infinity{ std::numeric_limits<double>::infinity() };
		constexpr auto nan{ std::numeric_limits<double>::quiet_NaN() };

		EXPECT_THROW(body.setMass(infinity), std::invalid_argument);
		EXPECT_DOUBLE_EQ(body.getMass(), initialMass);
		EXPECT_THROW(body.setMass(nan), std::invalid_argument);
		EXPECT_DOUBLE_EQ(body.getMass(), initialMass);
	}

	TEST(BodyTests, SetVelocityChangesVelocity)
	{
		auto body{ createTestBody(1.0) };
		const math::Vector3D velocity{ 10.0, 20.0, 30.0 };

		body.setVelocity(velocity);

		EXPECT_EQ(body.getVelocity(), velocity);
	}

	TEST(BodyTests, SetVelocityRejectsSpeedOfLightAndPreservesState)
	{
		const math::Vector3D initialVelocity{ 10.0, 20.0, 30.0 };
		auto body{ createTestBody(1.0, math::Vector3D{}, initialVelocity) };

		const math::Vector3D invalidVelocity{ physics::C_CONST, 0.0, 0.0 };

		EXPECT_THROW(body.setVelocity(invalidVelocity), std::invalid_argument);
		EXPECT_EQ(body.getVelocity(), initialVelocity);
	}

	TEST(BodyTests, ConstructorRejectsSpeedOfLightVelocity)
	{
		EXPECT_THROW((Body{ "A", BodyTypeId::Meteor, 1.0, math::Vector3D{}, math::Vector3D{ physics::C_CONST, 0.0, 0.0 } }), std::invalid_argument);
	}
} // namespace body::tests
