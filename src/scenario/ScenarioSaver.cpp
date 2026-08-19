#include "scenario/ScenarioSaver.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <ostream>
#include <string>
#include "common/RuntimeChecks.hpp"
#include "filesystem/ApplicationPaths.hpp"
#include "filesystem/FileNameValidation.hpp"
#include "scenario/Scenario.hpp"
#include "scenario/ScenarioFileFormat.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"

namespace
{
	namespace fs = std::filesystem;

	fs::path buildFilePath(const std::string& fileBaseName)
	{
		return ApplicationPaths::scenariosDirectory() / (fileBaseName + std::string{ ScenarioFileFormat::extension });
	}

	void serializeBody(std::ostream& output, const Body& body)
	{
		output << body.getName() << '\n'
			<< BodyTypeCatalog::getSerializationKey(body.getTypeId()) << ' '
			<< body.getMass() << ' '
			<< body.getPosition() << ' '
			<< body.getVelocity() << '\n';
	}

	void serializeScenario(std::ostream& output, const Scenario& scenario)
	{
		const auto& bodies{ scenario.bodies };
		output << std::setprecision(std::numeric_limits<double>::max_digits10);
		output << ScenarioFileFormat::identifier << ' '
			<< ScenarioFileFormat::currentVersion << '\n'
			<< scenario.name << '\n'
			<< bodies.size() << '\n';
		for (const auto& body : bodies) {
			serializeBody(output, body);
		}
	}

	void validateBaseName(const std::string& name, const char* errorMessage)
	{
		RuntimeChecks::ensure(FileNameValidation::isValidBaseName(name), RuntimeChecks::Type::Argument, errorMessage);
	}

	void validateNames(const std::string& saveName, const std::string& scenarioName)
	{
		validateBaseName(saveName, "Invalid scenario save file base name");
		validateBaseName(scenarioName, "Invalid scenario name");
	}
} // anonymous namespace

namespace ScenarioSaver
{

SaveResult save(const Scenario& scenario, const std::string& saveName, OverwritePolicy policy)
{
	validateNames(saveName, scenario.name);

	const auto filePath{ buildFilePath(saveName) };

	if (fs::exists(filePath) &&
		policy == OverwritePolicy::Deny) {
		return SaveResult::FileAlreadyExists;
	}

	fs::create_directories(filePath.parent_path());

	std::ofstream file{ filePath };
	RuntimeChecks::ensure(file.is_open(), RuntimeChecks::Type::Runtime, "Failed to open scenario file");

	serializeScenario(file, scenario);

	file.close();
	RuntimeChecks::ensure(!file.fail(), RuntimeChecks::Type::Runtime, "Failed to write scenario file");

	return SaveResult::Saved;
}

std::string getNextAvailableSaveName(const std::string& baseName)
{
	validateBaseName(baseName, "Invalid scenario save file base name");
	for (auto version{ 2 };; ++version) {
		const std::string candidate{ baseName + '_' + std::to_string(version) };

		if (!fs::exists(buildFilePath(candidate))) {
			return candidate;
		}
	}
}

} // ScenarioSaver
