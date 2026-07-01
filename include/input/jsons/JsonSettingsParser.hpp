#pragma once
#include "JsonParserBase.hpp"
#include <string>
#include <string_view>
#include <utility>

class JsonSettingsParser : private JsonParserBase
{
public:
	JsonSettingsParser(std::string_view data) : JsonParserBase{ data } {}
	std::string takeLanguageCode() { return std::move(m_languageCode); }
	void parse();
private:
	std::string m_languageCode{};
};
