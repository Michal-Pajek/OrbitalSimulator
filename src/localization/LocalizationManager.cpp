#include "localization/LocalizationManager.hpp"
#include <stdexcept>
#include <utility>
#include "localization/TextIdEntries.hpp"
#include "input/JsonLocalizationLoader.hpp"

LocalizationManager::LocalizationManager()
{
	setLanguage(DEFAULT_LANGUAGE);
}

LocalizationManager& LocalizationManager::getInstance()
{
	static LocalizationManager instance{};
	return instance;
}

void LocalizationManager::setLanguage(Language language)
{
	auto newMap{ JsonLocalizationLoader::loadData(getLanguageCode(language)) };
	setLocalizationMap(std::move(newMap));
	m_currentLanguage = language;
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

std::string_view LocalizationManager::getLanguageCode(Language language)
{
	switch (language) {
	case Language::English:
		return "en_US";
	case Language::Polish:
		return "pl_PL";
	default:
		throw std::runtime_error("Unsupported language");
	}
}

LocalizationManager::YesAndNo LocalizationManager::getYn() const
{
	switch (m_currentLanguage) {
	case Language::English:
		return YesAndNo{ .yes = 'Y', .no = 'N' };
	case Language::Polish:
		return YesAndNo{ .yes = 'T', .no = 'N' };
	default:
		throw std::runtime_error("Unsupported language");
	}
}
