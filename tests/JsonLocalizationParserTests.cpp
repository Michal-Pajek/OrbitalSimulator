#include <gtest/gtest.h>
#include <stdexcept>
#include <string_view>
#include "input/JsonLocalizationParser.hpp"

TEST(JsonLocalizationParserTests, ParsesOneValidEntry)
{
	std::string_view input{ R"({"texts":{"accept":"Accept"}})" };

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 1u);
	ASSERT_TRUE(data.contains("accept"));
	EXPECT_EQ(data.at("accept"), "Accept");
}

TEST(JsonLocalizationParserTests, ParsesMultipleValidEntries)
{
	std::string_view input{ R"({"texts":{"accept":"Accept","exit":"Exit","main_menu":"Main menu"}})" };

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 3u);
	EXPECT_EQ(data.at("accept"), "Accept");
	EXPECT_EQ(data.at("exit"), "Exit");
	EXPECT_EQ(data.at("main_menu"), "Main menu");
}

TEST(JsonLocalizationParserTests, AllowsWhitespaceBetweenTokens)
{
	std::string_view input{
		R"({
			"texts" : {
				"accept" : "Accept",
				"exit"   : "Exit"
			}
		})"
	};

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 2u);
	EXPECT_EQ(data.at("accept"), "Accept");
	EXPECT_EQ(data.at("exit"), "Exit");
}

TEST(JsonLocalizationParserTests, ParsesUtf8Text)
{
	std::string_view input{ R"({"texts":{"exit":"Wyjście","add_body":"Dodaj obiekt"}})" };

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 2u);
	EXPECT_EQ(data.at("exit"), "Wyjście");
	EXPECT_EQ(data.at("add_body"), "Dodaj obiekt");
}

TEST(JsonLocalizationParserTests, ParsesEscapedQuote)
{
	std::string_view input{ R"({"texts":{"quote":"He said \"Hi\""}})" };

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 1u);
	EXPECT_EQ(data.at("quote"), "He said \"Hi\"");
}

TEST(JsonLocalizationParserTests, ParsesEscapedBackslash)
{
	std::string_view input{ R"({"texts":{"path":"C:\\Temp"}})" };

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 1u);
	EXPECT_EQ(data.at("path"), "C:\\Temp");
}

TEST(JsonLocalizationParserTests, ParsesEscapedNewline)
{
	std::string_view input{ R"({"texts":{"line":"first\nsecond"}})" };

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 1u);
	EXPECT_EQ(data.at("line"), "first\nsecond");
}

TEST(JsonLocalizationParserTests, ParsesEscapedTab)
{
	std::string_view input{ R"({"texts":{"tab":"a\tb"}})" };

	JsonLocalizationParser parser{ input };
	parser.parse();

	const auto data{ parser.takeLocalizationData() };

	ASSERT_EQ(data.size(), 1u);
	EXPECT_EQ(data.at("tab"), "a\tb");
}

TEST(JsonLocalizationParserTests, ThrowsForEmptyInput)
{
	std::string_view input{ "" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenRootIsNotObject)
{
	std::string_view input{ R"("texts")" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenTextsKeyIsMissing)
{
	std::string_view input{ R"({"abc":{"accept":"Accept"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenTextsKeyHasTypo)
{
	std::string_view input{ R"({"text":{"accept":"Accept"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenColonAfterTextsIsMissing)
{
	std::string_view input{ R"({"texts"{"accept":"Accept"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenTextsValueIsNotObject)
{
	std::string_view input{ R"({"texts":"accept"})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForEmptyTextsObject)
{
	std::string_view input{ R"({"texts":{}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForDuplicateKey)
{
	std::string_view input{ R"({"texts":{"accept":"Accept","accept":"Akceptuj"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenColonBetweenKeyAndValueIsMissing)
{
	std::string_view input{ R"({"texts":{"accept" "Accept"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenValueIsMissing)
{
	std::string_view input{ R"({"texts":{"accept":}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenValueIsNotString)
{
	std::string_view input{ R"({"texts":{"accept":123}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenValueIsNull)
{
	std::string_view input{ R"({"texts":{"accept":null}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForTrailingComma)
{
	std::string_view input{ R"({"texts":{"accept":"Accept",}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsWhenCommaBetweenEntriesIsMissing)
{
	std::string_view input{ R"({"texts":{"accept":"Accept" "exit":"Exit"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForMissingClosingTextsBrace)
{
	std::string_view input{ R"({"texts":{"accept":"Accept")" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForMissingClosingRootBrace)
{
	std::string_view input{ R"({"texts":{"accept":"Accept"})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForTrailingGarbage)
{
	std::string_view input{ R"({"texts":{"accept":"Accept"}}abc)" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForExtraRootField)
{
	std::string_view input{ R"({"texts":{"accept":"Accept"},"extra":"x"})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForUnknownEscapeSequence)
{
	std::string_view input{ R"({"texts":{"bad":"abc\q"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForUnsupportedUnicodeEscapeSequence)
{
	std::string_view input{ R"({"texts":{"unicode":"\u0142"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForUnclosedString)
{
	std::string_view input{ R"({"texts":{"bad":"abc}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForEmptyKey)
{
	std::string_view input{ R"({"texts":{"":"value"}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}

TEST(JsonLocalizationParserTests, ThrowsForEmptyValue)
{
	std::string_view input{ R"({"texts":{"key":""}})" };

	JsonLocalizationParser parser{ input };

	EXPECT_THROW(parser.parse(), std::runtime_error);
}
