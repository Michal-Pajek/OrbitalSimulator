#include <cstddef>
#include <gtest/gtest.h>
#include <stdexcept>

#include "simulation/bodies/types/BodyType.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"

TEST(BodyTypesTests, GetTypeExceptions)
{
	for (std::size_t idx{}; idx < BODY_TYPE_COUNT; ++idx) {
		EXPECT_NO_THROW(BodyTypeCatalog::getType(static_cast<BodyTypeId>(idx)));
	}
	EXPECT_THROW(BodyTypeCatalog::getType(static_cast<BodyTypeId>(BODY_TYPE_COUNT)), std::logic_error);
}

TEST(BodyTypesTests, BodyTypeIdsMatchCatalogIndexes)
{
	for (std::size_t idx{}; idx < BODY_TYPE_COUNT; ++idx) {
		const auto bodyTypeId{ static_cast<BodyTypeId>(idx) };
		EXPECT_EQ(BodyTypeCatalog::getType(bodyTypeId).getId(), bodyTypeId);
	}
}

TEST(BodyTypesTests, AllMassIntervalsAreValid)
{
	for (const auto& bodyType : BodyTypeCatalog::getAvailableTypes()) {
		const auto interval{ bodyType.getMassInterval() };
		EXPECT_GT(interval.max, 0.0);
		EXPECT_GT(interval.min, 0.0);
		EXPECT_GT(interval.max, interval.min);
	}
}

TEST(BodyTypesTests, BodyTypesArraySizeEqualsBodyTypeCount)
{
	EXPECT_EQ(BodyTypeCatalog::getAvailableTypes().size(), BODY_TYPE_COUNT);
}
