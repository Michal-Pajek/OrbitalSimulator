#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "filesystem/FileNameValidation.hpp"

TEST(FileNameValidationTests, AcceptsValidBaseNames)
{
	constexpr std::string_view validNames[]{
		"scenario",
		"Earth_Moon",
		"Earth-Moon",
		"scenario.1",
		"Earth Moon",
	};

	for (const auto name : validNames) {
		SCOPED_TRACE(name);
		EXPECT_TRUE(FileNameValidation::isValidBaseName(name));
	}
}

TEST(FileNameValidationTests, RejectsEmptyName)
{
	EXPECT_FALSE(FileNameValidation::isValidBaseName(""));
}

TEST(FileNameValidationTests, RejectsCurrentAndParentDirectoryNames)
{
	EXPECT_FALSE(FileNameValidation::isValidBaseName("."));
	EXPECT_FALSE(FileNameValidation::isValidBaseName(".."));
}

TEST(FileNameValidationTests, RejectsForbiddenCharacters)
{
	constexpr std::string_view forbiddenCharacters{ "/\\<>:\"?*|" };

	for (const char forbiddenCharacter : forbiddenCharacters) {
		std::string name{ "scenario" };
		name.push_back(forbiddenCharacter);

		SCOPED_TRACE(
			::testing::Message{}
			<< "Character code: "
			<< static_cast<int>(forbiddenCharacter));

		EXPECT_FALSE(FileNameValidation::isValidBaseName(name));
	}
}

TEST(FileNameValidationTests, RejectsControlCharacters)
{
	for (unsigned int value{}; value < 32u; ++value) {
		std::string name{ "scenario" };
		name.push_back(static_cast<char>(value));

		SCOPED_TRACE(
			::testing::Message{}
			<< "Control character code: "
			<< value);

		EXPECT_FALSE(FileNameValidation::isValidBaseName(name));
	}
}

TEST(FileNameValidationTests, RejectsWindowsReservedNames)
{
	constexpr std::string_view invalidNames[]{
		"CON",
		"con",
		"CoN",
		"NUL.txt",
		"PRN.backup",
		"COM1",
		"com9",
		"COM1.txt",
		"LPT1",
		"lPt9.data"
	};

	for (const auto name : invalidNames) {
		SCOPED_TRACE(name);
		EXPECT_FALSE(FileNameValidation::isValidBaseName(name));
	}
}

TEST(FileNameValidationTests, RejectsTrailingSpaceOrPeriod)
{
	EXPECT_FALSE(FileNameValidation::isValidBaseName("scenario."));
	EXPECT_FALSE(FileNameValidation::isValidBaseName("scenario "));
}

TEST(FileNameValidationTests, AcceptsNamesSimilarToReservedNames)
{
	constexpr std::string_view validNames[]{
		"CONSOLE",
		"COM0",
		"COM10",
		"LPT0",
		"LPT10",
		"my.CON"
	};

	for (const auto name : validNames) {
		SCOPED_TRACE(name);
		EXPECT_TRUE(FileNameValidation::isValidBaseName(name));
	}
}
