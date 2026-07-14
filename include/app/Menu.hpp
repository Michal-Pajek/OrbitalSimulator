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
	MenuOption() = delete;
	MenuOption(const char optionKey, const TextId optionLabel, std::function<void()> optionAction) : key{ optionKey }, label{ optionLabel }, action{ std::move(optionAction) } {}
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
	void prepareKeysMap();
	void print() const;
	bool m_isHorizontal;
	std::vector<MenuOption> m_options{};
	std::unordered_map<char, size_t> m_keys{};
	TextId m_title;
};