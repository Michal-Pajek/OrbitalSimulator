#pragma once

class Recorder;
struct Scenario;
struct SimulationRunConfig;

namespace SimulationRunner
{
	void runAndRecord(Recorder& recorder, const Scenario& scenario, const SimulationRunConfig& config);
} // namespace SimulationRunner
