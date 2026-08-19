#include "input/jsons/JsonDataStorage.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include "app/ExceptionHandler.hpp"
#include "input/jsons/JsonLanguageSettingsParser.hpp"
#include "input/jsons/JsonLocalizationParser.hpp"

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
		ExceptionHandler::ensure(sourceFile.is_open(), ExceptionHandler::ExceptionType::Runtime, std::string{ "Could not open JSON file: " + path.string() }.c_str());
		std::stringstream buffer{};
		buffer << sourceFile.rdbuf();
		return buffer.str();
	}
} // anonymous namespace

namespace JsonDataStorage
{
	void saveLanguageCode(std::string_view languageCode)
	{
		std::ofstream file{ "resources/settings.json" };
		ExceptionHandler::ensure(file.is_open(), ExceptionHandler::ExceptionType::Runtime, "Could not open settings file for writing");

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
} // JsonDataStorage
