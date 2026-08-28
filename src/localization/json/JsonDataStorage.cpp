#include "localization/json/JsonDataStorage.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "localization/json/JsonLanguageSettingsParser.hpp"
#include "localization/json/JsonLocalizationParser.hpp"

#include "common/runtime_checks/RuntimeChecks.hpp"

namespace localization::json
{
	namespace
	{
		std::filesystem::path getLocalizationPath(std::string_view languageCode)
		{
			return std::filesystem::path{ "resources/localization" } /
				(std::string{ languageCode } + ".json");
		}

		std::string readWholeFile(const std::filesystem::path& path)
		{
			std::ifstream sourceFile{ path };
			runtime_checks::ensure(sourceFile.is_open(), runtime_checks::Type::Runtime, std::string{ "Could not open JSON file: " + path.string() }.c_str());
			std::stringstream buffer{};
			buffer << sourceFile.rdbuf();
			return buffer.str();
		}
	} // anonymous namespace

	void saveLanguageCode(std::string_view languageCode)
	{
		std::ofstream file{ "resources/settings.json" };
		runtime_checks::ensure(file.is_open(), runtime_checks::Type::Runtime, "Could not open settings file for writing");

		file << "{\n";
		file << " \"language\": \"" << languageCode << "\"\n";
		file << "}\n";
	}

	std::string loadLanguageCode()
	{
		const std::filesystem::path settingsPath{ "resources/settings.json" };
		const auto data{ readWholeFile(settingsPath) };
		JsonLanguageSettingsParser parser{ std::string_view{data} };
		parser.parse();
		return parser.takeLanguageCode();
	}

	LocalizationMap loadLocalizationData(std::string_view languageCode)
	{
		const auto localizationPath{ getLocalizationPath(languageCode) };
		const auto data{ readWholeFile(localizationPath) };
		JsonLocalizationParser parser{ std::string_view{data} };
		parser.parse();
		return parser.takeLocalizationData();
	}
} // namespace localization::json
