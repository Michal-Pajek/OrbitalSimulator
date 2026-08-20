#pragma once
#include "input/jsons/JsonParserBase.hpp"

#include <string_view>
#include <utility>

#include "localization/LocalizationTypes.hpp"

class JsonLocalizationParser : private JsonParserBase
{
public:
	JsonLocalizationParser(std::string_view data) : JsonParserBase{ data } {}
	LocalizationMap takeLocalizationData() { return std::move(m_localizationData); }
	void parse();
private:
	void parseTexts();
	LocalizationMap m_localizationData{};
};
