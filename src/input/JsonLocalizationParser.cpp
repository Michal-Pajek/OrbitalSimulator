#include "input/JsonLocalizationParser.hpp"
#include <stdexcept>

namespace
{
	constexpr auto INVALID_FILE{ "Invalid JSON file" };

	bool isWhiteMark(const char ch)
	{
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}

	void require(bool condition)
	{
		if (!condition) {
			throw std::runtime_error{ INVALID_FILE };
		}
	}
} // anonymous namespace

void JsonLocalizationParser::parse()
{
	require(expectChar('{'));
	require(expectString("texts"));
	require(expectChar(':'));
	require(expectChar('{'));
	parseTexts();
	require(expectChar('}'));
	require(expectChar('}'));
	skipWhiteMarks();
	require(m_pos == m_size);
}

bool JsonLocalizationParser::expectChar(const char ch)
{
	skipWhiteMarks();
	ensureCanRead();
	if (m_data[m_pos] == ch) {
		++m_pos;
		return true;
	}
	return false;
}

bool JsonLocalizationParser::expectString(std::string_view str)
{
	return getString() == str;
}

char JsonLocalizationParser::getEscapedChar()
{
	ensureCanRead();

	const char escaped{ m_data[m_pos++] };

	switch (escaped) {
	case '"':
		return '"';
	case '\\':
		return '\\';
	case '/':
		return '/';
	case 'n':
		return '\n';
	case 't':
		return '\t';
	case 'r':
		return '\r';
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'u':
		throw std::runtime_error{ "Unicode escape sequences are not supported yet" };
	default:
		throw std::runtime_error{ INVALID_FILE };
	}
}

void JsonLocalizationParser::parseTexts()
{
	do {
		const auto key{ getString() };
		require(expectChar(':'));
		const auto value{ getString() };
		require(!(key.empty() || value.empty()));
		const auto [it, inserted]{ m_localizationData.insert({ key, value }) };
		if (!inserted) {
			throw std::runtime_error{ "Duplicated localization key: " + it->first };
		}
		skipWhiteMarks();
		ensureCanRead();
		if (m_data[m_pos] == ',') {
			++m_pos;
		}
		else {
			return;
		}
	} while (true);
}

void JsonLocalizationParser::ensureCanRead() const
{
	if (m_pos >= m_size) {
		throw std::runtime_error{ INVALID_FILE };
	}
}

void JsonLocalizationParser::skipWhiteMarks()
{
	while (m_pos < m_size && isWhiteMark(m_data[m_pos])) {
		++m_pos;
	}
}

std::string JsonLocalizationParser::getString()
{
	require(expectChar('"'));
	std::string result{};
	while (m_pos < m_size) {
		const auto ch{ m_data[m_pos] };
		if (ch == '"') {
			++m_pos;
			return result;
		}
		if (ch == '\\') {
			++m_pos;
			result += getEscapedChar();
			continue;
		}
		const auto unsignedCh{ static_cast<unsigned char>(ch) };
		require(unsignedCh >= 0x20);
		result += ch;
		++m_pos;
	}
	throw std::runtime_error{ INVALID_FILE };
}
