#pragma once
#include <string>
#include <string_view>
#include <utility>
#include "TextId.hpp"
#include "LocalizationTypes.hpp"

class LocalizationManager
{
public:
	static inline constexpr std::string_view ENGLISH{ "en_US" };
	static inline constexpr std::string_view POLISH{ "pl_PL" };

	static LocalizationManager& getInstance();
	void loadLanguage(std::string_view languageCode);
	std::string get(TextId textId) const;
private:
	LocalizationManager();
	LocalizationManager(const LocalizationManager&) = delete;
	LocalizationManager(LocalizationManager&&) = delete;
	LocalizationManager& operator=(const LocalizationManager&) = delete;
	LocalizationManager& operator=(LocalizationManager&&) = delete;
	void setLocalizationMap(LocalizationMap data) { m_localizationMap = std::move(data); }
	LocalizationMap m_localizationMap{};
};
