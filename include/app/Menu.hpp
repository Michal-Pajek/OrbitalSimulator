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
	MenuOption(const char _key, const TextId _label, std::function<void()> _action) : key{ _key }, label{ _label }, action{ std::move(_action) } {}
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