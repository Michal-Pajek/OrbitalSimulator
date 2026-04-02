#include "app/Menu.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include "input/Keyboard.hpp"

Menu::Menu(const std::vector<MenuOption>& menuInput, const std::string& text, const bool horizontal) : m_menuOptions{menuInput}, m_text{text}, m_horizontal{horizontal}
{
	if (!validateMenuOptions(menuInput)) {
		throw std::invalid_argument("Menu input is incorrect");
	}
	prepareKeysMap();
}

void Menu::execute() const
{
	print();
	char key{};
	do {
		key = getSingleKey();
	} while (m_keys.find(key) == m_keys.end());
	m_menuOptions.at(m_keys.at(key)).func();
}

bool Menu::yesOrNo()
{
	std::cout << " [Y / N]: ";
	char choice{getSingleKey()};
	while (choice != 'N' && choice != 'Y') {
		choice = getSingleKey();
	}
	return choice == 'Y';
}

bool Menu::validateMenuOptions(const std::vector<MenuOption>& menuInput) const
{
	if (menuInput.empty()) {
		return false;
	}
	std::unordered_set<char> keys{};
	for (const auto& x : menuInput) {
		const auto key{ x.key };
		if (x.label.empty()) {
			return false;
		}
		if (key != static_cast<char>(std::toupper(static_cast<unsigned char>(key)))) {
			return false;
		}
		if (!x.func) {
			return false;
		}
		if (keys.find(key) != keys.end()) {
			return false;
		}
		keys.insert(key);
	}
	return true;
}

void Menu::prepareKeysMap()
{
	const auto size{ m_menuOptions.size() };
	for (size_t i{}; i < size; ++i) {
		m_keys.insert({ m_menuOptions[i].key, i });
	}
}

void Menu::print() const
{
	std::cout << "=== " << m_text << " ===\n";
	const auto separator{ m_horizontal ? '\t' : '\n' };
	for (const auto& x : m_menuOptions) {
		std::cout << "\t[ " << x.key << " ]\t" << x.label << separator;
	}
	if (m_horizontal) {
		std::cout << '\n';
	}
}