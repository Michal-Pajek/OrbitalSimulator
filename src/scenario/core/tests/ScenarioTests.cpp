#include <cstddef>
#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>
#include <vector>

#include "scenario/core/Scenario.hpp"

#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/tests/support/TestBodyCreator.hpp"

namespace
{
	std::vector<Body> createBodies(const std::size_t count)
	{
		std::vector<Body> bodies{};
		bodies.reserve(count);

		for (std::size_t i{}; i < count; ++i) {
			bodies.push_back(TestBodyCreator::createTestBody(1.0));
		}

		return bodies;
	}
}

TEST(ScenarioTests, ConstructorThrowsForEmptyBodyList)
{
	EXPECT_THROW((Scenario{ "Scenario", std::vector<Body>{} }), std::invalid_argument);
}

TEST(ScenarioTests, ConstructorAcceptsMaximumBodyCount)
{
	const Scenario scenario{ "Scenario", createBodies(Scenario::MAX_BODY_COUNT) };

	EXPECT_EQ(scenario.bodies.size(), Scenario::MAX_BODY_COUNT);
}

TEST(ScenarioTests, ConstructorThrowsWhenMaximumBodyCountIsExceeded)
{
	auto bodies{ createBodies(Scenario::MAX_BODY_COUNT + 1u) };

	EXPECT_THROW((Scenario{ "Scenario", std::move(bodies) }), std::invalid_argument);
}
