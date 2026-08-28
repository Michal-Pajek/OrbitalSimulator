#pragma once
#include <string>
#include <string_view>

#include "localization/core/LocalizationTypes.hpp"

namespace localization::json
{
	void saveLanguageCode(std::string_view languageCode);
	std::string loadLanguageCode();
	LocalizationMap loadLocalizationData(std::string_view languageCode);
} // namespace localization::json
