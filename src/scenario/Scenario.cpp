#include "scenario/Scenario.hpp"
#include <iostream>
#include "simulation/Body.hpp"
#include "simulation/Simulation.hpp"

Scenario::Scenario() : m_name{ "test simulation" }, m_bodies { createBodies() }
{
	// temp version
}

void Scenario::run()
{
	std::ofstream file{};
	if (!prepareCSVfile(file)) {
		std::cout << "Could not open the file\n";
		return;
	}
	Simulation simulation{ m_bodies, m_dt };
	runAndRecordSimulation(file, simulation);
	std::cout << "File generated successfully\n";
}

bool Scenario::prepareCSVfile(std::ofstream& file)
{
	file.open("testScenario.csv");
	if (file.is_open()) {
		file << "step,time,body_name,x,y,vx,vy\n";
		for (const auto& body : m_bodies) {
			writeSingleSnapshotToCSV(file, body);
		}
		return true;
	}
	return false;
}

void Scenario::recordStateAfterStep(std::ofstream& file, const Simulation& simulation, const unsigned int stepNo)
{
	const auto bodyCount{ simulation.getBodyCount() };
	const auto time{ simulation.getTime() };
	for (size_t i{}; i < bodyCount; ++i) {
		writeSingleSnapshotToCSV(file, simulation.getBody(i), stepNo, time);
	}
}

void Scenario::runAndRecordSimulation(std::ofstream& file, Simulation& simulation)
{
	constexpr unsigned int STEPS{ 100u };
	for (unsigned int i{}; i < STEPS;) {
		simulation.step();
		recordStateAfterStep(file, simulation, ++i);
	}
}

void Scenario::writeBodyStateToFile(const Body& body, std::ofstream& file)
{
	constexpr auto SEPARATOR{ ',' };
	file << body.getName() << SEPARATOR;
	const auto& pos{ body.getPosition() };
	file << pos.getX() << SEPARATOR;
	file << pos.getY() << SEPARATOR;
	const auto& vel{ body.getVelocity() };
	file << vel.getX() << SEPARATOR;
	file << vel.getY() << '\n';
}

void Scenario::writeSingleSnapshotToCSV(std::ofstream& file, const Body& body, const unsigned int stepNo, const double time)
{
	constexpr auto SEPARATOR{ ',' };
	file << stepNo << SEPARATOR << time << SEPARATOR;
	writeBodyStateToFile(body, file);
}

std::vector<Body> Scenario::createBodies()
{
	std::vector<Body> result{};
	result.reserve(2u);
	result.emplace_back(Body{ "body1", 1e14, Vector2D{}, Vector2D{1.0, 0.0} });
	result.emplace_back(Body{ "body2", 2e14, Vector2D{100.0, 100.0}, Vector2D{0.0, -1.0} });
	return result;
}
