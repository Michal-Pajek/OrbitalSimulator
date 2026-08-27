#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "body/Body.hpp"

class Simulation;

class Recorder
{
public:
	explicit Recorder(const std::string& fileBaseName);
	bool beginRecording();
	void recordInitialState(const std::vector<body::Body>& bodies);
	void recordStateAfterStep(const Simulation& simulation, const unsigned int stepNo);
private:
	static constexpr int OUTPUT_PRECISION{ 17 };
	void writeBodyStateToFile(const body::Body& body);
	void writeInitialSnapshotToCSV(const body::Body& body) { writeSingleSnapshotToCSV(body, 0u, 0.0); }
	void writeSingleSnapshotToCSV(const body::Body& body, const unsigned int stepNo, const double time);
	std::filesystem::path getPath() const;
	const std::string m_fileBaseName;
	std::ofstream m_file;
};
