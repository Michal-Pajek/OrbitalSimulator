#include "runner/SimulationRunner.hpp"

#include "common/runtime_checks/RuntimeChecks.hpp"
#include "recording/recorder.hpp"
#include "simulation/core/Simulation.hpp"
#include "simulation/run_config/SimulationRunConfig.hpp"
#include "scenario/core/Scenario.hpp"

namespace SimulationRunner
{
	void runAndRecord(recording::Recorder& recorder, const Scenario& scenario, const SimulationRunConfig& config)
	{
		const auto steps{ config.stepCount };
		const auto& bodies{ scenario.bodies };
		runtime_checks::ensure(recorder.beginRecording(), runtime_checks::Type::Runtime, "Could not open output file");
		Simulation simulation{ bodies, config.timeStep };
		recorder.recordInitialState(bodies);
		for (unsigned int i{}; i < steps;) {
			simulation.step();
			recorder.recordStateAfterStep(simulation, ++i);
		}
	}
} // namespace SimulationRunner
