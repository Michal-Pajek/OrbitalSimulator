#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class Body;
class Simulation;

class Recorder
{
public:
	Recorder(const std::string& fileName) : m_fileName{ fileName } {}
	bool beginRecording();
	void recordInitialState(const std::vector<Body>& bodies);
	void recordStateAfterStep(const Simulation& simulation, const unsigned int stepNo);
private:
	static constexpr int OUTPUT_PRECISION{ 17 };
	void writeBodyStateToFile(const Body& body);
	void writeInitialSnapshotToCSV(const Body& body) { writeSingleSnapshotToCSV(body, 0u, 0.0); }
	void writeSingleSnapshotToCSV(const Body& body, const unsigned int stepNo, const double time);
	std::filesystem::path getPath() const;
	const std::string m_fileName;
	std::ofstream m_file;
};
