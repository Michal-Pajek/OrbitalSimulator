#pragma once

class Recorder;
class Scenario;

class SimulationRunner
{
public:
	SimulationRunner() = delete;
	static void runAndRecord(Recorder& recorder, const Scenario& scenario);
};