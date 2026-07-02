#include "localization/LocalizationManager.hpp"
#include <utility>
#include "localization/TextIdEntries.hpp"
#include "input/jsons/JsonDataStorage.hpp"

LocalizationManager::LocalizationManager()
{
	applyLanguage(loadSavedLanguageOrDefault());
}

LocalizationManager& LocalizationManager::getInstance()
{
	static LocalizationManager instance{};
	return instance;
}

void LocalizationManager::setLanguage(const Language language)
{
	applyLanguage(language);
	saveLanguage(language);
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

TextId LocalizationManager::getCurrentLanguageTextId() const
{
	return findLanguageEntry(
		[this](const LanguageEntry& entry) {
			return entry.language == m_currentLanguage;
		},
		"Unidentified language"
	).name;
}

LocalizationManager::YesAndNo LocalizationManager::getYn() const
{
	switch (m_currentLanguage) {
	case Language::English:
		return YesAndNo{ .yes = 'Y', .no = 'N' };
	case Language::Polish:
		return YesAndNo{ .yes = 'T', .no = 'N' };
	default:
		throw std::runtime_error{ "Unsupported language" };
	}
}

void LocalizationManager::applyLanguage(const Language language)
{
	if (!m_languageApplied || m_currentLanguage != language) {
		auto newMap{ JsonDataStorage::loadLocalizationData(getLanguageCode(language)) };
		setLocalizationMap(std::move(newMap));
		m_currentLanguage = language;
		m_languageApplied = true;
	}
}

void LocalizationManager::saveLanguage(const Language language)
{
	JsonDataStorage::saveLanguageCode(getLanguageCode(language));
}

LocalizationManager::Language LocalizationManager::getLanguageFromCode(std::string_view languageCode)
{
	return findLanguageEntry(
		[languageCode](const LanguageEntry& entry) {
			return entry.code == languageCode;
		},
		"Unsupported language code"
	).language;
}

LocalizationManager::Language LocalizationManager::loadSavedLanguageOrDefault()
{
	try {
		const auto languageCode{ JsonDataStorage::loadLanguageCode() };
		return getLanguageFromCode(languageCode);
	}
	catch (...) {
		return DEFAULT_LANGUAGE;
	}
}

std::string_view LocalizationManager::getLanguageCode(const Language language)
{
	return findLanguageEntry(
		[language](const LanguageEntry& entry) {
			return entry.language == language;
		},
		"Unsupported language"
	).code;
}
