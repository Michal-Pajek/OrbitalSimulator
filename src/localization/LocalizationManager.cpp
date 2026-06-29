#include "localization/LocalizationManager.hpp"
#include "localization/TextIdEntries.hpp"
#include "input/JsonLocalizationLoader.hpp"

LocalizationManager::LocalizationManager()
{
	loadLanguage(ENGLISH);
}

LocalizationManager& LocalizationManager::getInstance()
{
	static LocalizationManager instance{};
	return instance;
}

void LocalizationManager::loadLanguage(std::string_view languageCode)
{
	setLocalizationMap(JsonLocalizationLoader::loadData(languageCode));
}

std::string LocalizationManager::get(TextId textId) const
{
	const std::string key{ TextIdEntries::toLocalizationKey(textId) };
	const auto it{ m_localizationMap.find(key) };
	if (it != m_localizationMap.end()) {
		return it->second;
	}
	return "<ERROR: MISSING TRANSLATION: " + key + ">";
}
