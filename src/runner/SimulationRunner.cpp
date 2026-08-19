#include "runner/SimulationRunner.hpp"
#include "app/ExceptionHandler.hpp"
#include "recording/Recorder.hpp"
#include "simulation/Simulation.hpp"
#include "simulation/SimulationRunConfig.hpp"
#include "scenario/Scenario.hpp"

namespace SimulationRunner
{
	void runAndRecord(Recorder& recorder, const Scenario& scenario, const SimulationRunConfig& config)
	{
		const auto steps{ config.stepCount };
		const auto& bodies{ scenario.bodies };
		ExceptionHandler::ensure(recorder.beginRecording(), ExceptionHandler::ExceptionType::Runtime, "Could not open output file");
		Simulation simulation{ bodies, config.timeStep };
		recorder.recordInitialState(bodies);
		for (unsigned int i{}; i < steps;) {
			simulation.step();
			recorder.recordStateAfterStep(simulation, ++i);
		}
	}
}
