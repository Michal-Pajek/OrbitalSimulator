#include "localization/json/JsonParserBase.hpp"

#include <stdexcept>

#include "common/RuntimeChecks.hpp"

void JsonParserBase::require(const bool condition)
{
	RuntimeChecks::ensure(condition, RuntimeChecks::Type::Runtime, INVALID_FILE);
}

bool JsonParserBase::expectChar(const char ch)
{
	skipWhiteMarks();
	ensureCanRead();
	if (m_data[m_pos] == ch) {
		++m_pos;
		return true;
	}
	return false;
}

bool JsonParserBase::expectString(std::string_view str)
{
	return getString() == str;
}

char JsonParserBase::getEscapedChar()
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

void JsonParserBase::ensureCanRead() const
{
	RuntimeChecks::ensure(m_pos < m_size, RuntimeChecks::Type::Runtime, INVALID_FILE);
}

void JsonParserBase::skipWhiteMarks()
{
	while (m_pos < m_size && isWhiteMark(m_data[m_pos])) {
		++m_pos;
	}
}

std::string JsonParserBase::getString()
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
