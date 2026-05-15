#include "runner/SimulationRunner.hpp"
#include <stdexcept>
#include "recording/Recorder.hpp"
#include "simulation/Simulation.hpp"
#include "scenario/Scenario.hpp"

void SimulationRunner::runAndRecord(Recorder& recorder, const Scenario& scenario)
{
	const auto steps{ scenario.stepCount };
	const auto& bodies{ scenario.bodies };
	if (!recorder.beginRecording()) {
		throw std::runtime_error("Could not open output file.");
	}
	Simulation simulation{ bodies, scenario.timeStep };
	recorder.recordInitialState(bodies);
	for (unsigned int i{}; i < steps;) {
		simulation.step();
		recorder.recordStateAfterStep(simulation, ++i);
	}
}