#pragma once
#include "localization/json/JsonParserBase.hpp"

#include <string>
#include <string_view>
#include <utility>

class JsonLanguageSettingsParser : private JsonParserBase
{
public:
	JsonLanguageSettingsParser(std::string_view data) : JsonParserBase{ data } {}
	std::string takeLanguageCode() { return std::move(m_languageCode); }
	void parse();
private:
	std::string m_languageCode{};
};
