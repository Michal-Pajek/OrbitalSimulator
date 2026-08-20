#pragma once
#include <array>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "localization/LocalizationTypes.hpp"
#include "localization/TextId.hpp"

class LocalizationManager
{
public:
	enum class Language
	{
		English,
		Polish,
	};

	struct YesAndNo
	{
		char yes;
		char no;
	};

	static LocalizationManager& getInstance();
	void setLanguage(const Language language);
	std::string get(TextId textId) const;
	TextId getCurrentLanguageTextId() const;
	YesAndNo getYn() const;
private:
	static inline constexpr auto DEFAULT_LANGUAGE{ Language::English };

	struct LanguageEntry
	{
		Language language;
		std::string_view code;
		TextId name;
	};

	static inline constexpr std::array languageEntries{
		LanguageEntry{Language::English,	"en_US",	TextId::English},
		LanguageEntry{Language::Polish,		"pl_PL",	TextId::Polish}
	};

	LocalizationManager();
	LocalizationManager(const LocalizationManager&) = delete;
	LocalizationManager(LocalizationManager&&) = delete;
	LocalizationManager& operator=(const LocalizationManager&) = delete;
	LocalizationManager& operator=(LocalizationManager&&) = delete;
	void applyLanguage(const Language language);
	void saveLanguage(const Language language);
	void setLocalizationMap(LocalizationMap data) { m_localizationMap = std::move(data); }
	static Language getLanguageFromCode(std::string_view languageCode);
	static Language loadSavedLanguageOrDefault();
	static std::string_view getLanguageCode(const Language language);
	bool m_languageApplied{ false };
	Language m_currentLanguage{ DEFAULT_LANGUAGE };
	LocalizationMap m_localizationMap{};

	template <typename Predicate>
	static const LanguageEntry& findLanguageEntry(const Predicate& predicate, const char* errorMessage)
	{
		for (const auto& entry : languageEntries) {
			if (predicate(entry)) {
				return entry;
			}
		}
		throw std::runtime_error{ errorMessage };
	}
};
