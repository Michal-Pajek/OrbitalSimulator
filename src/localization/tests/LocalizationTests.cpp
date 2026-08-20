#include <cstddef>
#include <gtest/gtest.h>
#include <set>
#include <string_view>

#include "localization/TextId.hpp"
#include "localization/TextIdEntries.hpp"

TEST(LocalizationTests, TextIdEntriesAreOrderedByTextIdValue)
{
	for (std::size_t idx{}; idx < TEXT_ID_COUNT; ++idx) {
		EXPECT_EQ(static_cast<TextId>(idx), TextIdEntries::textIdEntries[idx].id);
	}
}

TEST(LocalizationTests, TextIdEntriesKeysAreNotEmpty)
{
	for (const auto& entry : TextIdEntries::textIdEntries) {
		EXPECT_FALSE(entry.key.empty());
	}
}

TEST(LocalizationTests, TextIdEntriesKeysAreUnique)
{
	std::set<std::string_view> keys;

	for (const auto& entry : TextIdEntries::textIdEntries) {
		EXPECT_TRUE(keys.insert(entry.key).second) << entry.key;
	}
}
