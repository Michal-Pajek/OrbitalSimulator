#include <iomanip>
#include <ios>
#include "app/ApplicationPaths.hpp"
#include "recording/Recorder.hpp"
#include "simulation/bodies/Body.hpp"
#include "simulation/Simulation.hpp"

bool Recorder::beginRecording()
{
	m_file.open(getPath());
	if (m_file.is_open()) {
		m_file << std::scientific << std::setprecision(OUTPUT_PRECISION);
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
	namespace fs = std::filesystem;
	const fs::path filePath{ ApplicationPaths::simulationsDirectory() / (m_fileName + ".csv") };
	fs::create_directories(filePath.parent_path());
	return filePath;
}
