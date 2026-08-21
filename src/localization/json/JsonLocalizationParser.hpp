#pragma once
#include "localization/json/JsonParserBase.hpp"

#include <string_view>
#include <utility>

#include "localization/core/LocalizationTypes.hpp"

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
