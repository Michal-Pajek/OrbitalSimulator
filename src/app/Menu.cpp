#include "app/Menu.hpp"
#include <cctype>
#include <stdexcept>
#include <unordered_set>
#include "input/Keyboard.hpp"
#include "ui/ConsoleWriter.hpp"

Menu::Menu(const std::vector<MenuOption>& options, const TextId title, const bool isHorizontal) : m_options{options}, m_title{title}, m_isHorizontal{isHorizontal}
{
	if (!validateMenuOptions(options)) {
		throw std::invalid_argument("Menu input is incorrect");
	}
	prepareKeysMap();
}

void Menu::execute() const
{
	if (m_options.size() == 1u) {
		m_options.at(0u).action();
		return;
	}
	print();
	char key{};
	do {
		key = getSingleKey();
	} while (m_keys.find(key) == m_keys.end());
	m_options.at(m_keys.at(key)).action();
}

bool Menu::yesOrNo(const TextId question)
{
	ConsoleWriter::write(question);
	const auto yn{ Localization::getYn() };
	ConsoleWriter::writeYesOrNo(yn);
	char choice{getSingleKey()};
	while (choice != yn.yes && choice != yn.no) {
		choice = getSingleKey();
	}
	ConsoleWriter::writeLine();
	return choice == yn.yes;
}

bool Menu::validateMenuOptions(const std::vector<MenuOption>& options) const
{
	if (options.empty()) {
		return false;
	}
	std::unordered_set<char> keys{};
	for (const auto& x : options) {
		const auto key{ x.key };
		if (key != static_cast<char>(std::toupper(static_cast<unsigned char>(key)))) {
			return false;
		}
		if (!x.action) {
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
	const auto size{ m_options.size() };
	m_keys.reserve(size);
	for (size_t i{}; i < size; ++i) {
		m_keys.insert({ m_options[i].key, i });
	}
}

void Menu::print() const
{
	ConsoleWriter::writeMenuTitle(m_title);
	const auto separator{ m_isHorizontal ? '\t' : '\n' };
	for (const auto& x : m_options) {
		ConsoleWriter::writeMenuOption(x.label, x.key, separator);
	}
	if (m_isHorizontal) {
		ConsoleWriter::writeLine();
	}
}

// TEMP
double getUnitMultiplier(const std::vector<MenuOptionPair>& options, const TextId menuTitle)
{
	const auto size{ options.size() };
	if (size == 0 || size >= 10u) {
		throw std::invalid_argument("Options vector in getUnitMultiplier must be between 1 and 9");
	}

	double result{};
	TextId selectedUnit;
	auto key{ '1' };
	std::vector<MenuOption> menuOptions{};
	menuOptions.reserve(size);
	for (size_t idx{}; idx < size; ++idx) {
		const auto& multiplier{ options.at(idx).multiplier };
		const auto& textId{ options.at(idx).textId };
		menuOptions.emplace_back(key++, textId, [&result, &selectedUnit, multiplier, textId]() {result = multiplier; selectedUnit = textId; });
	}

	const Menu selectUnitMenu{ menuOptions, menuTitle };
	selectUnitMenu.execute();
	ConsoleWriter::writeLine(TextId::SelectedUnit, ": ", selectedUnit);
	return result;
}
// END OF TEMP