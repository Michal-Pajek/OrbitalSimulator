#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "ui/menu/Menu.hpp"

namespace
{
	MenuOption createOption(const char key, const TextId label, const bool isVisible = true)
	{
		return MenuOption{ key, label, []() {}, isVisible };
	}
}

TEST(MenuTests, MenuOptionIsVisibleByDefault)
{
	const MenuOption option{ 'A', TextId::Accept, []() {} };

	EXPECT_TRUE(option.isVisible);
}

TEST(MenuTests, MenuOptionCanBeCreatedAsNotVisible)
{
	const MenuOption option{ 'A', TextId::Accept, []() {}, false };

	EXPECT_FALSE(option.isVisible);
}

TEST(MenuTests, ConstructorDoesNotThrowWhenInvisibleOptionDuplicatesVisibleKey)
{
	const std::vector<MenuOption> options{
		createOption('A', TextId::Accept),
		createOption('A', TextId::Cancel, false)
	};

	EXPECT_NO_THROW((Menu{ options, TextId::QuestionWhatDoYouWantToDo }));
}

TEST(MenuTests, ConstructorThrowsWhenVisibleOptionsHaveDuplicatedKeys)
{
	const std::vector<MenuOption> options{
		createOption('A', TextId::Accept),
		createOption('A', TextId::Cancel)
	};

	EXPECT_THROW((Menu{ options, TextId::QuestionWhatDoYouWantToDo }), std::invalid_argument);
}

TEST(MenuTests, ConstructorThrowsWhenAllOptionsAreInvisible)
{
	const std::vector<MenuOption> options{
		createOption('A', TextId::Accept, false),
		createOption('C', TextId::Cancel, false)
	};

	EXPECT_THROW((Menu{ options, TextId::QuestionWhatDoYouWantToDo }), std::invalid_argument);
}
