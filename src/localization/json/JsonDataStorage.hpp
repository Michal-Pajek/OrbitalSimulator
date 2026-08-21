#pragma once
#include <string>
#include <string_view>

#include "localization/core/LocalizationTypes.hpp"

namespace JsonDataStorage
{
	void saveLanguageCode(std::string_view languageCode);
	std::string loadLanguageCode();
	LocalizationMap loadLocalizationData(std::string_view languageCode);
} // namespace JsonDataStorage
