#pragma once
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "localization/core/TextId.hpp"

namespace ui
{
	struct MenuOption
	{
		char key;
		localization::TextId label;
		std::function<void()> action;
		bool isVisible;
		MenuOption() = delete;
		MenuOption(const char optionKey, const localization::TextId optionLabel, std::function<void()> optionAction, const bool visibility = true)
			: key{ optionKey }, label{ optionLabel }, action{ std::move(optionAction) }, isVisible{ visibility } {
		}
	};

	class Menu
	{
	public:
		Menu() = delete;
		Menu(const std::vector<MenuOption>& options, const localization::TextId title, const bool isHorizontal = false);
		void execute() const;
		static bool yesOrNo(const localization::TextId question);
	private:
		bool validateMenuOptions(const std::vector<MenuOption>& options) const;
		void eraseNonVisibleOptions();
		void prepareKeysMap();
		void print() const;
		bool m_isHorizontal;
		std::vector<MenuOption> m_options{};
		std::unordered_map<char, size_t> m_keys{};
		localization::TextId m_title;
	};
} // namespace ui
