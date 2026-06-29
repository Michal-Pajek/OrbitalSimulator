#pragma once
#include <string_view>
#include "localization/LocalizationTypes.hpp"

namespace JsonLocalizationLoader
{
	LocalizationMap loadData(std::string_view languageCode);
}
