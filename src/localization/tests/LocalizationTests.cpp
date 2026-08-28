#include <cstddef>
#include <gtest/gtest.h>
#include <set>
#include <string_view>

#include "localization/core/TextId.hpp"
#include "localization/core/TextIdEntries.hpp"

namespace localization::tests
{
	TEST(LocalizationTests, TextIdEntriesAreOrderedByTextIdValue)
	{
		for (std::size_t idx{}; idx < TEXT_ID_COUNT; ++idx) {
			EXPECT_EQ(static_cast<TextId>(idx), text_id_entries::textIdEntries[idx].id);
		}
	}

	TEST(LocalizationTests, TextIdEntriesKeysAreNotEmpty)
	{
		for (const auto& entry : text_id_entries::textIdEntries) {
			EXPECT_FALSE(entry.key.empty());
		}
	}

	TEST(LocalizationTests, TextIdEntriesKeysAreUnique)
	{
		std::set<std::string_view> keys;

		for (const auto& entry : text_id_entries::textIdEntries) {
			EXPECT_TRUE(keys.insert(entry.key).second) << entry.key;
		}
	}
} // namespace localization::tests
