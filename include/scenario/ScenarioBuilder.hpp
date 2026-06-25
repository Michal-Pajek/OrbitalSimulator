#pragma once
#include <optional>
#include <string>
#include <vector>
#include "scenario/Scenario.hpp"
#include "simulation/bodies/Body.hpp"

class ScenarioBuilder
{
public:
	ScenarioBuilder() = default;
	std::optional<Scenario> buildScenario();
private:
	bool reviewAndConfirmScenario();
	void createBodiesFromInput();
	void printBodies(const bool printHeadline = true) const;
	void printScenarioSummary() const;
	void promptForScenarioName();
	void promptForStepCount();
	void promptForTimeStep();
	void resetState();
	void reviewAndEditBodies();
	void reviseScenario();
	double m_timeStep{};
	unsigned int m_stepCount{};
	std::string m_name{};
	std::vector<Body> m_bodies{};
};
