#include "app/Menu.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include "input/Keyboard.hpp"
#include "localization/Localization.hpp"

Menu::Menu(const std::vector<MenuOption>& menuInput, const TextId text, const bool horizontal) : m_menuOptions{menuInput}, m_text{text}, m_horizontal{horizontal}
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

bool Menu::yesOrNo(const TextId question)
{
	std::cout << Localization::translate(question);
	const auto yn{ Localization::getYn() };
	std::cout << " [" << yn.yes << " / " << yn.no << "]: ";
	char choice{getSingleKey()};
	while (choice != yn.yes && choice != yn.no) {
		choice = getSingleKey();
	}
	return choice == yn.yes;
}

bool Menu::validateMenuOptions(const std::vector<MenuOption>& menuInput) const
{
	if (menuInput.empty()) {
		return false;
	}
	std::unordered_set<char> keys{};
	for (const auto& x : menuInput) {
		const auto key{ x.key };
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
	std::cout << "=== " << Localization::translate(m_text) << " ===\n";
	const auto separator{ m_horizontal ? '\t' : '\n' };
	for (const auto& x : m_menuOptions) {
		std::cout << "\t[ " << x.key << " ]\t" << Localization::translate(x.label) << separator;
	}
	if (m_horizontal) {
		std::cout << '\n';
	}
}