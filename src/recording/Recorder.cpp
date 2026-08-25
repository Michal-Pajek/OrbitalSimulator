#include "recording/Recorder.hpp"

#include <iomanip>
#include <ios>

#include "body/Body.hpp"
#include "common/runtime_checks/RuntimeChecks.hpp"
#include "filesystem/ApplicationPaths.hpp"
#include "filesystem/FileNameValidation.hpp"
#include "simulation/core/Simulation.hpp"

Recorder::Recorder(const std::string& fileBaseName) : m_fileBaseName{ fileBaseName }
{
	RuntimeChecks::ensure(FileNameValidation::isValidBaseName(m_fileBaseName), RuntimeChecks::Type::Argument, "Invalid recording file base name");
}

bool Recorder::beginRecording()
{
	namespace fs = std::filesystem;

	const auto path{ getPath() };
	fs::create_directories(path.parent_path());
	m_file.open(path);

	if (m_file.is_open()) {
		m_file << std::scientific
			<< std::setprecision(OUTPUT_PRECISION);
		m_file << "step,time,body_name,x,y,z,vx,vy,vz\n";
		return true;
	}

	return false;
}

void Recorder::recordInitialState(const std::vector<Body>& bodies)
{
	for (const auto& body : bodies) {
		writeInitialSnapshotToCSV(body);
	}
}

void Recorder::recordStateAfterStep(const Simulation& simulation, const unsigned int stepNo)
{
	const auto bodyCount{ simulation.getBodyCount() };
	const auto time{ simulation.getTime() };
	for (size_t i{}; i < bodyCount; ++i) {
		writeSingleSnapshotToCSV(simulation.getBody(i), stepNo, time);
	}
}

void Recorder::writeBodyStateToFile(const Body& body)
{
	constexpr auto SEPARATOR{ ',' };
	m_file << body.getName() << SEPARATOR;
	const auto& pos{ body.getPosition() };
	m_file << pos.getX() << SEPARATOR;
	m_file << pos.getY() << SEPARATOR;
	m_file << pos.getZ() << SEPARATOR;
	const auto& vel{ body.getVelocity() };
	m_file << vel.getX() << SEPARATOR;
	m_file << vel.getY() << SEPARATOR;
	m_file << vel.getZ() << '\n';
}

void Recorder::writeSingleSnapshotToCSV(const Body& body, const unsigned int stepNo, const double time)
{
	constexpr auto SEPARATOR{ ',' };
	m_file << stepNo << SEPARATOR << time << SEPARATOR;
	writeBodyStateToFile(body);
}

std::filesystem::path Recorder::getPath() const
{
	return ApplicationPaths::simulationsDirectory() / (m_fileBaseName + ".csv");
}
