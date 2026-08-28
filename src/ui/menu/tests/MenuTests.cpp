#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "ui/menu/Menu.hpp"

namespace ui::tests
{
	namespace
	{
		MenuOption createOption(const char key, const localization::TextId label, const bool isVisible = true)
		{
			return MenuOption{ key, label, []() {}, isVisible };
		}
	} // anonymous namespace

	TEST(MenuTests, MenuOptionIsVisibleByDefault)
	{
		const MenuOption option{ 'A', localization::TextId::Accept, []() {} };

		EXPECT_TRUE(option.isVisible);
	}

	TEST(MenuTests, MenuOptionCanBeCreatedAsNotVisible)
	{
		const MenuOption option{ 'A', localization::TextId::Accept, []() {}, false };

		EXPECT_FALSE(option.isVisible);
	}

	TEST(MenuTests, ConstructorDoesNotThrowWhenInvisibleOptionDuplicatesVisibleKey)
	{
		const std::vector<MenuOption> options{
			createOption('A', localization::TextId::Accept),
			createOption('A', localization::TextId::Cancel, false)
		};

		EXPECT_NO_THROW((Menu{ options, localization::TextId::QuestionWhatDoYouWantToDo }));
	}

	TEST(MenuTests, ConstructorThrowsWhenVisibleOptionsHaveDuplicatedKeys)
	{
		const std::vector<MenuOption> options{
			createOption('A', localization::TextId::Accept),
			createOption('A', localization::TextId::Cancel)
		};

		EXPECT_THROW((Menu{ options, localization::TextId::QuestionWhatDoYouWantToDo }), std::invalid_argument);
	}

	TEST(MenuTests, ConstructorThrowsWhenAllOptionsAreInvisible)
	{
		const std::vector<MenuOption> options{
			createOption('A', localization::TextId::Accept, false),
			createOption('C', localization::TextId::Cancel, false)
		};

		EXPECT_THROW((Menu{ options, localization::TextId::QuestionWhatDoYouWantToDo }), std::invalid_argument);
	}
} // namespace ui::tests
