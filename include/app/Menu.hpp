#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include "localization/TextId.hpp"

struct MenuOption
{
	char key;
	TextId label;
	std::function<void()> func;
};

class Menu
{
public:
	Menu() = delete;
	Menu(const std::vector<MenuOption>& menuInput, const TextId text, const bool horizontal = false);
	void execute() const;
	static bool yesOrNo(const TextId question);
private:
	bool validateMenuOptions(const std::vector<MenuOption>& menuInput) const;
	void prepareKeysMap();
	void print() const;
	bool m_horizontal;
	std::vector<MenuOption> m_menuOptions{};
	std::unordered_map<char, size_t> m_keys{};
	TextId m_text;
};