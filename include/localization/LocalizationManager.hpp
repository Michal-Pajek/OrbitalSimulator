#pragma once
#include <string>
#include <string_view>
#include <utility>
#include "TextId.hpp"
#include "LocalizationTypes.hpp"

class LocalizationManager
{
public:
	enum class Language
	{
		English,
		Polish
	};

	struct YesAndNo
	{
		char yes;
		char no;
	};

	static LocalizationManager& getInstance();
	void setLanguage(Language language);
	std::string get(TextId textId) const;
	Language getCurrentLanguage() const { return m_currentLanguage; }
	YesAndNo getYn() const;
private:
	static inline constexpr Language DEFAULT_LANGUAGE{ Language::English };
	LocalizationManager();
	LocalizationManager(const LocalizationManager&) = delete;
	LocalizationManager(LocalizationManager&&) = delete;
	LocalizationManager& operator=(const LocalizationManager&) = delete;
	LocalizationManager& operator=(LocalizationManager&&) = delete;
	void setLocalizationMap(LocalizationMap data) { m_localizationMap = std::move(data); }
	static std::string_view getLanguageCode(Language language);
	Language m_currentLanguage{ DEFAULT_LANGUAGE };
	LocalizationMap m_localizationMap{};
};
