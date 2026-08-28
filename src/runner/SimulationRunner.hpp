#pragma once

namespace recording
{
	class Recorder;
} // namespace recording

struct Scenario;
struct SimulationRunConfig;

namespace SimulationRunner
{
	void runAndRecord(recording::Recorder& recorder, const Scenario& scenario, const SimulationRunConfig& config);
} // namespace SimulationRunner
