#pragma once
#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include "localization/LocalizationTypes.hpp"

class JsonLocalizationParser
{
public:
	JsonLocalizationParser(std::string_view data) : m_data{ data }, m_size{ data.size() } {}
	LocalizationMap takeLocalizationData() { return std::move(m_localizationData); }
	void parse();
private:
	bool expectChar(const char ch);
	bool expectString(std::string_view str);
	char getEscapedChar();
	void parseTexts();
	void ensureCanRead() const;
	void skipWhiteMarks();
	std::string getString();
	LocalizationMap m_localizationData{};
	std::string_view m_data{};
	std::size_t m_pos{};
	const std::size_t m_size;
};
