#include <gtest/gtest.h>
#include <set>
#include <string>
#include <string_view>
#include "input/jsons/JsonDataStorage.hpp"
#include "localization/TextIdEntries.hpp"

namespace
{
	static inline constexpr std::string_view ENGLISH{ "en_US" };
	static inline constexpr std::string_view POLISH{ "pl_PL" };

std::set<std::string> getExpectedLocalizationKeys()
{
	std::set<std::string> keys{};

	for (const auto& entry : TextIdEntries::textIdEntries) {
		keys.insert(std::string{ entry.key });
	}

	return keys;
}

void expectJsonContainsAllTextIdEntries(const LocalizationMap& localizationMap)
{
	for (const auto& entry : TextIdEntries::textIdEntries) {
		const std::string key{ entry.key };

		EXPECT_TRUE(localizationMap.contains(key)) << "Missing key in JSON: " << key;
	}
}

void expectJsonDoesNotContainUnknownKeys(const LocalizationMap& localizationMap)
{
	const auto expectedKeys{ getExpectedLocalizationKeys() };

	for (const auto& entry : localizationMap) {
		const auto& key{ entry.first };
		EXPECT_TRUE(expectedKeys.contains(key)) << "Unknown key in JSON: " << key;
	}
}

void expectJsonHasExpectedEntryCount(const LocalizationMap& localizationMap)
{
	EXPECT_EQ(localizationMap.size(), TEXT_ID_COUNT);
}

} // anonymous namespace

TEST(LocalizationResourcesTests, EnglishJsonContainsAllTextIdEntries)
{
	const auto localizationMap{ JsonDataStorage::loadLocalizationData(ENGLISH) };

	expectJsonContainsAllTextIdEntries(localizationMap);
}

TEST(LocalizationResourcesTests, PolishJsonContainsAllTextIdEntries)
{
	const auto localizationMap{ JsonDataStorage::loadLocalizationData(POLISH) };

	expectJsonContainsAllTextIdEntries(localizationMap);
}

TEST(LocalizationResourcesTests, EnglishJsonDoesNotContainUnknownKeys)
{
	const auto localizationMap{ JsonDataStorage::loadLocalizationData(ENGLISH) };

	expectJsonDoesNotContainUnknownKeys(localizationMap);
}

TEST(LocalizationResourcesTests, PolishJsonDoesNotContainUnknownKeys)
{
	const auto localizationMap{ JsonDataStorage::loadLocalizationData(POLISH) };

	expectJsonDoesNotContainUnknownKeys(localizationMap);
}

TEST(LocalizationResourcesTests, EnglishJsonHasExpectedEntryCount)
{
	const auto localizationMap{ JsonDataStorage::loadLocalizationData(ENGLISH) };

	expectJsonHasExpectedEntryCount(localizationMap);
}

TEST(LocalizationResourcesTests, PolishJsonHasExpectedEntryCount)
{
	const auto localizationMap{ JsonDataStorage::loadLocalizationData(POLISH) };

	expectJsonHasExpectedEntryCount(localizationMap);
}

TEST(LocalizationResourcesTests, EnglishAndPolishJsonHaveSameKeys)
{
	const auto englishMap{ JsonDataStorage::loadLocalizationData(ENGLISH) };
	const auto polishMap{ JsonDataStorage::loadLocalizationData(POLISH) };

	for (const auto& entry : englishMap) {
		const auto& key{ entry.first };
		EXPECT_TRUE(polishMap.contains(key)) << "Missing key in pl_PL.json: " << key;
	}

	for (const auto& entry : polishMap) {
		const auto& key{ entry.first };
		EXPECT_TRUE(englishMap.contains(key)) << "Missing key in en_US.json: " << key;
	}
}
