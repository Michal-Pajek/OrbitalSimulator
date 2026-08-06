#include "scenario/ScenarioLoader.hpp"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>
#include "app/Menu.hpp"
#include "filesystem/ApplicationPaths.hpp"
#include "filesystem/FileNameValidation.hpp"
#include "input/DataGetter.hpp"
#include "localization/TextId.hpp"
#include "math/Vector3D.hpp"
#include "scenario/ScenarioFileFormat.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	namespace fs = std::filesystem;

	bool hasOnlyWhitespaceRemaining(std::istream& stream)
	{
		stream >> std::ws;
		return stream.eof();
	}

	bool removeSaveExtension(std::string& filename)
	{
		const auto size{ filename.size() };
		const auto extensionSize{ ScenarioFileFormat::extension.size() };
		if (size < (extensionSize + 1u)) {
			return false;
		}
		const auto threshold{ size - extensionSize };
		const auto substr{ filename.substr(threshold) };
		if (substr != ScenarioFileFormat::extension) {
			return false;
		}
		filename.erase(threshold);
		return true;
	}

	void removeTrailingCarriageReturn(std::string& line)
	{
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
	}

	bool validateFileHeader(std::istream& file)
	{
		std::string headerLine;
		if (!std::getline(file, headerLine)) {
			return false;
		}

		std::istringstream headerStream{ headerLine };
		std::string identifier;
		int version{};

		if (!(headerStream >> identifier >> version) ||
			identifier != ScenarioFileFormat::identifier ||
			version != ScenarioFileFormat::currentVersion ||
			!hasOnlyWhitespaceRemaining(headerStream)) {
			return false;
		}

		return true;
	}

	std::optional<Vector3D> deserializeVector(std::istream& file)
	{
		char openingBracket{};
		char firstSeparator{};
		char secondSeparator{};
		char closingBracket{};

		double x{};
		double y{};
		double z{};

		if (!(file >> openingBracket
			>> x
			>> firstSeparator
			>> y
			>> secondSeparator
			>> z
			>> closingBracket)) {
			return {};
		}

		if (openingBracket != '[' ||
			firstSeparator != ';' ||
			secondSeparator != ';' ||
			closingBracket != ']') {
			return {};
		}

		try {
			return Vector3D{ x, y, z };
		}
		catch (const std::invalid_argument&) {
			return {};
		}
	}

	std::optional<Body> deserializeBody(std::istream& file)
	{
		std::string name;
		std::string bodyDataLine;

		if (!std::getline(file, name) ||
			!std::getline(file, bodyDataLine)) {
			return {};
		}

		removeTrailingCarriageReturn(name);

		if (name.empty()) {
			return {};
		}

		std::istringstream bodyData{ bodyDataLine };
		std::string serializationKey;
		double mass{};

		if (!(bodyData >> serializationKey >> mass)) {
			return {};
		}

		const auto bodyTypeIdOpt{
			BodyTypeCatalog::deserializeKey(serializationKey)
		};
		const auto positionOpt{ deserializeVector(bodyData) };
		const auto velocityOpt{ deserializeVector(bodyData) };

		if (!bodyTypeIdOpt ||
			!positionOpt ||
			!velocityOpt ||
			!hasOnlyWhitespaceRemaining(bodyData)) {
			return {};
		}

		try {
			return Body{
				name,
				*bodyTypeIdOpt,
				mass,
				*positionOpt,
				*velocityOpt
			};
		}
		catch (const std::invalid_argument&) {
			return {};
		}
	}

	void printFileNames(const std::vector<std::string>& fileNames)
	{
		const auto namesCount{ fileNames.size() };
		for (std::size_t idx{}; idx < namesCount; ++idx) {
			ConsoleWriter::writeLine(idx + 1u, ". ", fileNames.at(idx));
		}
	}

	fs::path buildSaveFilePath(const std::string& fileBaseName)
	{
		return ApplicationPaths::scenariosDirectory() / (fileBaseName + std::string{ ScenarioFileFormat::extension });
	}

	std::optional<fs::path> selectSaveFileFromList(const std::vector<std::string>& fileNames)
	{
		printFileNames(fileNames);
		ConsoleWriter::write(TextId::EnterScenarioNumberOrZeroToCancel, ": ");
		const auto namesCount{ static_cast<int>(fileNames.size()) };
		const auto idx{ static_cast<std::size_t>(DataGetter::getValue<int>([namesCount](const int value) {return 0 <= value && value <= namesCount; })) };
		std::optional<fs::path> result{};
		if (idx > 0u) {
			result = buildSaveFilePath(fileNames.at(idx - 1u));
		}
		return result;
	}

	std::optional<fs::path> selectSaveFile(const std::vector<std::string>& fileNames)
	{
		const auto count{ fileNames.size() };
		if (count == 1u) {
			ConsoleWriter::writeLine(TextId::ThereIsOnlyOneSavedScenario, ": ", fileNames.front());
			std::optional<fs::path> result{};
			if (Menu::yesOrNo(TextId::QuestionDoYouWantToLoadIt)) {
				result = buildSaveFilePath(fileNames.front());
			}
			return result;
		}
		return selectSaveFileFromList(fileNames);
	}

	std::optional<Scenario> deserializeScenario(std::istream& file)
	{
		std::string scenarioName;
		if (!std::getline(file, scenarioName)) {
			return {};
		}

		removeTrailingCarriageReturn(scenarioName);

		if (!FileNameValidation::isValidBaseName(scenarioName)) {
			return {};
		}

		std::string bodiesCountLine;
		if (!std::getline(file, bodiesCountLine)) {
			return {};
		}

		std::istringstream countStream{ bodiesCountLine };

		long long bodiesCount{};
		if (!(countStream >> bodiesCount) ||
			!hasOnlyWhitespaceRemaining(countStream) ||
			bodiesCount <= 0 ||
			bodiesCount > static_cast<long long>(Scenario::MAX_BODY_COUNT)) {
			return {};
		}

		const auto count{ static_cast<std::size_t>(bodiesCount) };
		std::vector<Body> bodies{};
		bodies.reserve(count);

		for (std::size_t i{}; i < count; ++i) {
			auto bodyOpt{ deserializeBody(file) };
			if (!bodyOpt) {
				return {};
			}

			bodies.push_back(std::move(*bodyOpt));
		}

		file >> std::ws;
		if (file.peek() != std::char_traits<char>::eof()) {
			return {};
		}

		return Scenario{ std::move(scenarioName), std::move(bodies) };
	}

	std::vector<std::string> findSaveFiles()
	{
		const auto folderPath{ ApplicationPaths::scenariosDirectory() };
		std::vector<std::string> result{};
		try {
			for (const auto& entry : fs::directory_iterator{ folderPath }) {
				if (entry.is_regular_file()) {
					auto filename{ entry.path().filename().string() };
					if (removeSaveExtension(filename)) {
						result.push_back(filename);
					}
				}
			}
		}
		catch (const fs::filesystem_error& error) {
			if (error.code() == std::errc::no_such_file_or_directory) {
				return {};
			}
			throw;
		}
		std::ranges::sort(result);
		return result;
	}
} // anonymous namespace

namespace ScenarioLoader
{
	LoadResult getScenario()
	{
		const auto saveFiles{ findSaveFiles() };
		if (saveFiles.empty()) {
			return { LoadStatus::NoSavedScenarios, {} };
		}

		const auto fileOpt{ selectSaveFile(saveFiles) };
		if (!fileOpt) {
			return { LoadStatus::Canceled, {} };
		}

		std::ifstream file{ *fileOpt };
		if (!file) {
			return { LoadStatus::Failed, {} };
		}
		if (!validateFileHeader(file)) {
			return { LoadStatus::Failed, {} };
		}

		auto scenarioOpt{ deserializeScenario(file) };
		if (!scenarioOpt) {
			return { LoadStatus::Failed, {} };
		}

		return { LoadStatus::Loaded, std::move(scenarioOpt) };
	}
} // ScenarioLoader
