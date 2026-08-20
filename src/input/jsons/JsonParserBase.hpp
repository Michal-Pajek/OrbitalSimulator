#pragma once
#include <cstddef>
#include <string>
#include <string_view>

class JsonParserBase
{
protected:
	static inline constexpr auto INVALID_FILE{ "Invalid JSON file" };
	JsonParserBase(std::string_view data) : m_data{ data }, m_size{ data.size() } {}
	static bool isWhiteMark(const char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
	static void require(const bool condition);
	bool expectChar(const char ch);
	bool expectString(std::string_view str);
	char getEscapedChar();
	void ensureCanRead() const;
	void skipWhiteMarks();
	std::string getString();
	std::string_view m_data{};
	std::size_t m_pos{};
	const std::size_t m_size;
};
