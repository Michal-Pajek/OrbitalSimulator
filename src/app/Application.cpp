#include "app/Application.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "math/Vector2D.hpp"
#include "simulation/Body.hpp"
#include "simulation/Simulation.hpp"

namespace {

	std::vector<Body> createBodies()
	{
		std::vector<Body> result{};
		result.reserve(2u);
		result.emplace_back(Body{ "body1", 1e14, Vector2D{}, Vector2D{1.0, 0.0} });
		result.emplace_back(Body{ "body2", 2e14, Vector2D{100.0, 100.0}, Vector2D{0.0, -1.0} });
		return result;
	}

	void writeBodyStateToFile(const Body& body, std::ofstream& file)
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

	void writeSingleSnapshotToCSV(std::ofstream& file, const Body& body, const unsigned int stepNo = 0u, const double time = 0.0)
	{
		constexpr auto SEPARATOR{ ',' };
		file << stepNo << SEPARATOR << time << SEPARATOR;
		writeBodyStateToFile(body, file);
	}

	bool prepareCSVfile(std::ofstream& file, const std::vector<Body>& bodies)
	{
		file.open("testScenario.csv");
		if (file.is_open()) {
			file << "step,time,body_name,x,y,vx,vy\n";
			for (const auto& body : bodies) {
				writeSingleSnapshotToCSV(file, body);
			}
			return true;
		}
		return false;
	}

	void recordStateAfterStep(std::ofstream& file, const Simulation& simulation, const unsigned int stepNo)
	{
		const auto bodyCount{ simulation.getBodyCount() };
		const auto time{ simulation.getTime() };
		for (size_t i{}; i < bodyCount; ++i) {
			writeSingleSnapshotToCSV(file, simulation.getBody(i), stepNo, time);
		}
	}

	void runAndRecordSimulation(std::ofstream& file, Simulation& simulation)
	{
		constexpr unsigned int STEPS{ 100u };
		for (unsigned int i{}; i < STEPS;) {
			simulation.step();
			recordStateAfterStep(file, simulation, ++i);
		}
	}

	void runTestSimulation()
	{
		const auto bodies{ createBodies() };
		std::ofstream file{};
		if (!prepareCSVfile(file, bodies)) {
			std::cout << "Could not open the file\n";
			return;
		}
		Simulation simulation{ bodies };
		runAndRecordSimulation(file, simulation);
	}

} // anonymous namespace

void Application::run()
{
	runTestSimulation();
}
