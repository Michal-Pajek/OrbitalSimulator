#include "app/Menu.hpp"

#include <cctype>
#include <unordered_set>

#include "common/RuntimeChecks.hpp"
#include "input/Keyboard.hpp"
#include "localization/LocalizationManager.hpp"
#include "ui/ConsoleWriter.hpp"

Menu::Menu(const std::vector<MenuOption>& options, const TextId title, const bool isHorizontal) : m_options{options}, m_title{title}, m_isHorizontal{isHorizontal}
{
	eraseNonVisibleOptions();
	RuntimeChecks::ensure(validateMenuOptions(m_options), RuntimeChecks::Type::Argument, "Menu input is incorrect");
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
		key = Keyboard::getSingleKey();
	} while (m_keys.find(key) == m_keys.end());
	m_options.at(m_keys.at(key)).action();
}

bool Menu::yesOrNo(const TextId question)
{
	ConsoleWriter::write(question);
	const auto yn{ LocalizationManager::getInstance().getYn() };
	ConsoleWriter::writeYesOrNo(yn);
	char choice{ Keyboard::getSingleKey() };
	while (choice != yn.yes && choice != yn.no) {
		choice = Keyboard::getSingleKey();
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

void Menu::eraseNonVisibleOptions()
{
	std::erase_if(m_options, [](const auto& obj) {return !obj.isVisible; });
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
