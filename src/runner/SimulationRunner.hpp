#pragma once

namespace recording
{
	class Recorder;
} // namespace recording

namespace scenario
{
	struct Scenario;
} // namespace scenario

namespace simulation
{
	struct SimulationRunConfig;

	namespace runner
	{
		void runAndRecord(recording::Recorder& recorder, const scenario::Scenario& scenario, const SimulationRunConfig& config);
	} // namespace runner
} // namespace simulation
