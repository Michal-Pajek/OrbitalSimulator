#include "scenario/ScenarioSaver.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include "app/ApplicationPaths.hpp"
#include "scenario/Scenario.hpp"
#include "scenario/ScenarioFileFormat.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"

namespace
{
	namespace fs = std::filesystem;

	fs::path buildFilePath(const std::string& fileName)
	{
		return ApplicationPaths::scenariosDirectory() / (fileName + ".sav");
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
} // anonymous namespace

namespace ScenarioSaver
{

SaveResult save(const Scenario& scenario, const std::string& saveName, OverwritePolicy policy)
{
	const auto filePath{ buildFilePath(saveName) };

	if (fs::exists(filePath) &&
		policy == OverwritePolicy::Deny) {
		return SaveResult::FileAlreadyExists;
	}

	fs::create_directories(filePath.parent_path());

	std::ofstream file{ filePath };
	if (!file.is_open()) {
		throw std::runtime_error{ "Failed to open scenario file" };
	}

	serializeScenario(file, scenario);

	file.close();

	if (!file) {
		throw std::runtime_error{ "Failed to write scenario file" };
	}

	return SaveResult::Saved;
}

std::string getNextAvailableSaveName(const std::string& baseName)
{
	for (auto version{ 2 };; ++version) {
		const std::string candidate{ baseName + '_' + std::to_string(version) };

		if (!fs::exists(buildFilePath(candidate))) {
			return candidate;
		}
	}
}

} // ScenarioSaver
