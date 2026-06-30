#include "input/JsonLocalizationLoader.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "input/JsonLocalizationParser.hpp"

namespace
{
	std::filesystem::path getPath(std::string_view languageCode)
	{
		return std::filesystem::path{ "resources/localization" } /
			(std::string{ languageCode } + ".json");
	}

	std::string readWholeFile(std::string_view languageCode)
	{
		const auto path{ getPath(languageCode) };
		std::ifstream sourceFile{ path };
		if (!sourceFile.is_open()) {
			throw std::runtime_error{ "Could not open localization file: " + path.string() };
		}
		std::stringstream buffer{};
		buffer << sourceFile.rdbuf();
		return buffer.str();
	}
} // anonymous namespace

namespace JsonLocalizationLoader
{
	LocalizationMap loadData(std::string_view languageCode)
	{
		const auto data{ readWholeFile(languageCode) };
		JsonLocalizationParser parser{ std::string_view{data} };
		parser.parse();
		return parser.takeLocalizationData();
	}
} // JsonLocalizationLoader
