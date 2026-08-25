#include <cstddef>
#include <gtest/gtest.h>
#include <map>
#include <string_view>

#include "body/types/BodyType.hpp"
#include "body/types/BodyTypeCatalog.hpp"

TEST(BodyTypeCatalogTests, SerializationKeysRemainBackwardCompatible)
{
	const std::map<BodyTypeId, std::string_view> expectedMappings{
		{BodyTypeId::Meteor,		std::string_view{ "Meteor" }},
		{BodyTypeId::Asteroid,		std::string_view{ "Asteroid" }},
		{BodyTypeId::Comet,			std::string_view{ "Comet" }},
		{BodyTypeId::Moon,			std::string_view{ "Moon" }},
		{BodyTypeId::DwarfPlanet,	std::string_view{ "DwarfPlanet" }},
		{BodyTypeId::Planet,		std::string_view{ "Planet" }},
		{BodyTypeId::BrownDwarf,	std::string_view{ "BrownDwarf" }},
		{BodyTypeId::Star,			std::string_view{ "Star" }},
	};

	ASSERT_EQ(expectedMappings.size(), BODY_TYPE_COUNT);

	for (const auto& [id, expectedKey] : expectedMappings) {
		EXPECT_EQ(BodyTypeCatalog::getSerializationKey(id), expectedKey);

		const auto deserializedId{ BodyTypeCatalog::deserializeKey(expectedKey) };
		ASSERT_TRUE(deserializedId);
		EXPECT_EQ(*deserializedId, id);
	}
}

TEST(BodyTypeCatalogTests, DeserializeKeyReturnsEmptyForUnknownKey)
{
	EXPECT_FALSE(BodyTypeCatalog::deserializeKey("UnknownBodyType"));
}

TEST(BodyTypeCatalogTests, MassIntervalIncludesBothBoundaries)
{
	for (std::size_t idValue{}; idValue < BODY_TYPE_COUNT; ++idValue) {
		const auto id{ static_cast<BodyTypeId>(idValue) };
		const auto& [min, max]{ BodyTypeCatalog::getType(id).getMassInterval() };

		SCOPED_TRACE(
			::testing::Message{}
			<< "Body type id: "
			<< idValue);

		EXPECT_TRUE(BodyTypeCatalog::isMassInRange(id, min));
		EXPECT_TRUE(BodyTypeCatalog::isMassInRange(id, max));
	}
}
