#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct MenuOption
{
	char key;
	std::string label;
	std::function<void()> func;
};

class Menu
{
public:
	Menu() = delete;
	Menu(const std::vector<MenuOption>& menuInput, const std::string& text, const bool horizontal = false);
	void execute() const;
	static bool yesOrNo();
private:
	bool validateMenuOptions(const std::vector<MenuOption>& menuInput) const;
	void prepareKeysMap();
	void print() const;
	bool m_horizontal;
	std::vector<MenuOption> m_menuOptions{};
	std::unordered_map<char, size_t> m_keys{};
	std::string m_text;
};