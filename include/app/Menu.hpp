#pragma once
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
#include "localization/TextId.hpp"

struct MenuOption
{
	char key;
	TextId label;
	std::function<void()> action;
	bool isVisible;
	MenuOption() = delete;
	MenuOption(const char optionKey, const TextId optionLabel, std::function<void()> optionAction, const bool visibility = true)
		: key{ optionKey }, label{ optionLabel }, action{ std::move(optionAction) }, isVisible{ visibility } {}
};

class Menu
{
public:
	Menu() = delete;
	Menu(const std::vector<MenuOption>& options, const TextId title, const bool isHorizontal = false);
	void execute() const;
	static bool yesOrNo(const TextId question);
private:
	bool validateMenuOptions(const std::vector<MenuOption>& options) const;
	void eraseNonVisibleOptions();
	void prepareKeysMap();
	void print() const;
	bool m_isHorizontal;
	std::vector<MenuOption> m_options{};
	std::unordered_map<char, size_t> m_keys{};
	TextId m_title;
};