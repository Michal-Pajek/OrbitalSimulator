#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "simulation/Body.hpp"

class Simulation;

class Scenario
{
public:
	Scenario();
	void run();
private:
	bool prepareCSVfile(std::ofstream& file);
	void recordStateAfterStep(std::ofstream& file, const Simulation& simulation, const unsigned int stepNo);
	void runAndRecordSimulation(std::ofstream& file, Simulation& simulation);
	void writeBodyStateToFile(const Body& body, std::ofstream& file);
	void writeSingleSnapshotToCSV(std::ofstream& file, const Body& body, const unsigned int stepNo = 0u, const double time = 0.0);
	std::vector<Body> createBodies();
	double m_dt{ 1.0 };
	std::string m_name{};
	std::vector<Body> m_bodies{};
};