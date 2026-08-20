#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <string_view>

#include "input/jsons/JsonLanguageSettingsParser.hpp"

namespace
{
	std::string parseLanguageCode(std::string_view json)
	{
		JsonLanguageSettingsParser parser{ json };
		parser.parse();
		return parser.takeLanguageCode();
	}

	void expectThrowsFor(std::string_view json)
	{
		JsonLanguageSettingsParser parser{ json };
		EXPECT_THROW(parser.parse(), std::runtime_error);
	}
} // anonymous namespace

TEST(JsonLanguageSettingsParserTests, ParsesValidEnglishLanguageCode)
{
	const auto languageCode{ parseLanguageCode(R"({"language":"en_US"})") };

	EXPECT_EQ(languageCode, "en_US");
}

TEST(JsonLanguageSettingsParserTests, ParsesValidPolishLanguageCode)
{
	const auto languageCode{ parseLanguageCode(R"({"language":"pl_PL"})") };

	EXPECT_EQ(languageCode, "pl_PL");
}

TEST(JsonLanguageSettingsParserTests, AllowsWhitespaceBetweenTokens)
{
	const auto languageCode{ parseLanguageCode(R"(
		{
			"language"  :  "pl_PL"
		}
	)") };

	EXPECT_EQ(languageCode, "pl_PL");
}

TEST(JsonLanguageSettingsParserTests, ParsesUnknownLanguageCodeBecauseSemanticValidationIsDoneElsewhere)
{
	const auto languageCode{ parseLanguageCode(R"({"language":"de_DE"})") };

	EXPECT_EQ(languageCode, "de_DE");
}

TEST(JsonLanguageSettingsParserTests, ParsesEmptyLanguageCodeBecauseSemanticValidationIsDoneElsewhere)
{
	const auto languageCode{ parseLanguageCode(R"({"language":""})") };

	EXPECT_TRUE(languageCode.empty());
}

TEST(JsonLanguageSettingsParserTests, ThrowsForEmptyInput)
{
	expectThrowsFor("");
}

TEST(JsonLanguageSettingsParserTests, ThrowsWhenRootIsNotObject)
{
	expectThrowsFor(R"("language")");
}

TEST(JsonLanguageSettingsParserTests, ThrowsWhenLanguageKeyIsMissing)
{
	expectThrowsFor(R"({})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsWhenLanguageKeyHasTypo)
{
	expectThrowsFor(R"({"lang":"pl_PL"})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsWhenColonIsMissing)
{
	expectThrowsFor(R"({"language" "pl_PL"})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsWhenLanguageValueIsMissing)
{
	expectThrowsFor(R"({"language":})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsWhenLanguageValueIsNotString)
{
	expectThrowsFor(R"({"language":123})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsWhenLanguageValueIsNull)
{
	expectThrowsFor(R"({"language":null})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsForExtraRootField)
{
	expectThrowsFor(R"({"language":"pl_PL","theme":"dark"})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsForTrailingGarbage)
{
	expectThrowsFor(R"({"language":"pl_PL"} garbage)");
}

TEST(JsonLanguageSettingsParserTests, ThrowsForAnonymousNestedObject)
{
	expectThrowsFor(R"({
		{
			"language": "pl_PL"
		}
	})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsForMissingClosingRootBrace)
{
	expectThrowsFor(R"({"language":"pl_PL")");
}

TEST(JsonLanguageSettingsParserTests, ThrowsForUnclosedString)
{
	expectThrowsFor(R"({"language":"pl_PL})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsForUnknownEscapeSequence)
{
	expectThrowsFor(R"({"language":"pl\qPL"})");
}

TEST(JsonLanguageSettingsParserTests, ThrowsForUnsupportedUnicodeEscapeSequence)
{
	expectThrowsFor(R"({"language":"pl\u005FPL"})");
}
