#include <cstdlib>
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "simulation/core/Simulation.hpp"

#include "body/Body.hpp"
#include "body/tests/support/TestBodyCreator.hpp"
#include "math/Vector3D.hpp"

constexpr double EPSILON{ 1e-9 };

namespace
{

	std::vector<body::Body> createVectorWithTwoAsymmetricBodies()
	{
		std::vector<body::Body> bodyVec{};
		bodyVec.reserve(2u);
		bodyVec.emplace_back(body::tests::createTestBody(1e8, math::Vector3D{ 2.0, 3.0, 0.0 }, math::Vector3D{ 4.0, 5.0, 0.0 }, "body1"));
		bodyVec.emplace_back(body::tests::createTestBody(6e8, math::Vector3D{ 7.0, 8.0, 0.0 }, math::Vector3D{ 9.0, 10.0, 0.0 }, "body2"));
		return bodyVec;
	}

	std::vector<body::Body> createVectorWithTwoSymmetricBodies()
	{
		std::vector<body::Body> bodyVec{};
		bodyVec.reserve(2u);
		bodyVec.emplace_back(body::tests::createTestBody(1e9, math::Vector3D{ 10.0, 0.0, 0.0 }, math::Vector3D{ -2.0, 0.0, 0.0 }));
		bodyVec.emplace_back(body::tests::createTestBody(1e9, math::Vector3D{ 0.0, 10.0, 0.0 }, math::Vector3D{ 2.0, 0.0, 0.0 }));
		return bodyVec;
	}

	math::Vector3D calculateTotalMomentum(const Simulation& simulation)
	{
		math::Vector3D result{};
		const auto size{ simulation.getBodyCount() };
		for (size_t i{}; i < size; ++i) {
			const auto& body{ simulation.getBody(i) };
			result += body.getMass() * body.getVelocity();
		}
		return result;
	}

	double calculateRelativeError(const double reference, const double actual)
	{
		constexpr double INTERNAL_EPSILON{ 1e-12 };
		const auto absReference{ std::abs(reference) };
		if (absReference < INTERNAL_EPSILON) {
			return std::abs(reference - actual);
		}
		return std::abs(reference - actual) / absReference;
	}

} // anonymous namespace

TEST(SimulationTests, ReturnsCorrectBodyCount)
{
	std::vector<body::Body> bodyVec{};
	Simulation simulation1{ bodyVec };
	EXPECT_EQ(simulation1.getBodyCount(), 0u);

	bodyVec.emplace_back(body::tests::createTestBody(1.0, math::Vector3D{ 2.0, 3.0, 0.0 }, math::Vector3D{ 4.0, 5.0, 0.0 }));
	simulation1.setBodies(bodyVec);
	EXPECT_EQ(simulation1.getBodyCount(), 1u);

	bodyVec.emplace_back(body::tests::createTestBody(6.0, math::Vector3D{ 7.0, 8.0, 0.0 }, math::Vector3D{ 9.0, 10.0, 0.0 }));
	const Simulation simulation2{ bodyVec };
	EXPECT_EQ(simulation2.getBodyCount(), 2u);
}

TEST(SimulationTests, ReturnsCorrectBody)
{
	const auto bodyVec{ createVectorWithTwoAsymmetricBodies() };
	const Simulation simulation{ bodyVec };
	const auto& body1{ simulation.getBody(0u) };
	const auto& body2{ simulation.getBody(1u) };
	EXPECT_DOUBLE_EQ(body1.getMass(), 1e8);
	EXPECT_DOUBLE_EQ(body1.getPosition().getX(), 2.0);
	EXPECT_DOUBLE_EQ(body1.getPosition().getY(), 3.0);
	EXPECT_DOUBLE_EQ(body1.getPosition().getZ(), 0.0);
	EXPECT_DOUBLE_EQ(body1.getVelocity().getX(), 4.0);
	EXPECT_DOUBLE_EQ(body1.getVelocity().getY(), 5.0);
	EXPECT_DOUBLE_EQ(body1.getVelocity().getZ(), 0.0);
	EXPECT_DOUBLE_EQ(body2.getMass(), 6e8);
	EXPECT_DOUBLE_EQ(body2.getPosition().getX(), 7.0);
	EXPECT_DOUBLE_EQ(body2.getPosition().getY(), 8.0);
	EXPECT_DOUBLE_EQ(body2.getPosition().getZ(), 0.0);
	EXPECT_DOUBLE_EQ(body2.getVelocity().getX(), 9.0);
	EXPECT_DOUBLE_EQ(body2.getVelocity().getY(), 10.0);
	EXPECT_DOUBLE_EQ(body2.getVelocity().getZ(), 0.0);
	EXPECT_EQ(body1.getName(), "body1");
	EXPECT_EQ(body2.getName(), "body2");
}

TEST(SimulationTests, ThrowsForOutOfRangeIndex)
{
	const auto bodyVec{ createVectorWithTwoAsymmetricBodies() };
	const Simulation simulation{ bodyVec };
	EXPECT_THROW(simulation.getBody(2u), std::out_of_range);
}

TEST(SimulationTests, PreservesSymmetry)
{
	const auto bodyVec{ createVectorWithTwoSymmetricBodies() };
	Simulation simulation{ bodyVec };
	simulation.runSteps(10u);

	const auto& pos1{ simulation.getBody(0u).getPosition() };
	const auto& pos2{ simulation.getBody(1u).getPosition() };
	EXPECT_NEAR(pos1.getX() + pos2.getX(), 10.0, EPSILON);
	EXPECT_NEAR(pos1.getY() + pos2.getY(), 10.0, EPSILON);
	EXPECT_NEAR(pos1.getZ() + pos2.getZ(), 0.0, EPSILON);

	const auto& vel1{ simulation.getBody(0u).getVelocity() };
	const auto& vel2{ simulation.getBody(1u).getVelocity() };
	EXPECT_NEAR(vel1.getX() + vel2.getX(), 0.0, EPSILON);
	EXPECT_NEAR(vel1.getY() + vel2.getY(), 0.0, EPSILON);
	EXPECT_NEAR(vel1.getZ() + vel2.getZ(), 0.0, EPSILON);
}

TEST(SimulationTests, ConservesTotalMomentum)
{
	const auto bodyVec{ createVectorWithTwoAsymmetricBodies() };
	Simulation simulation{ bodyVec };
	const auto totalMomentumBefore{ calculateTotalMomentum(simulation) };
	simulation.runSteps(10u);
	const auto totalMomentumAfter{ calculateTotalMomentum(simulation) };
	EXPECT_LE(calculateRelativeError(totalMomentumBefore.getX(), totalMomentumAfter.getX()), EPSILON);
	EXPECT_LE(calculateRelativeError(totalMomentumBefore.getY(), totalMomentumAfter.getY()), EPSILON);
	EXPECT_LE(calculateRelativeError(totalMomentumBefore.getZ(), totalMomentumAfter.getZ()), EPSILON);
}

TEST(SimulationTests, AdvancesTimeCorrectly)
{
	constexpr double DT{ 2.0 };
	const auto bodyVec{ createVectorWithTwoAsymmetricBodies() };
	Simulation simulation{ bodyVec, DT };

	constexpr unsigned int N{ 20u };
	simulation.runSteps(N);
	EXPECT_DOUBLE_EQ(simulation.getTime(), N * DT);
}

TEST(SimulationTests, ResetsTimeAfterSettingBodies)
{
	const auto bodyVec{ createVectorWithTwoAsymmetricBodies() };
	Simulation simulation{ bodyVec };
	simulation.step();
	simulation.setBodies(bodyVec);
	EXPECT_DOUBLE_EQ(simulation.getTime(), 0.0);
}

TEST(SimulationTests, ThrowsWhenSteppingEmptySimulation)
{
	const std::vector<body::Body> bodyVec{};
	Simulation simulation{ bodyVec };
	EXPECT_THROW(simulation.step(), std::logic_error);
}

TEST(SimulationTests, ThrowsForNonPositiveDt)
{
	const std::vector<body::Body> bodyVec{};
	EXPECT_THROW((Simulation{ bodyVec, 0.0 }), std::invalid_argument);

	Simulation simulation{ bodyVec };
	EXPECT_THROW(simulation.setDt(0.0), std::invalid_argument);
	EXPECT_THROW(simulation.setDt(-1.0), std::invalid_argument);
}
