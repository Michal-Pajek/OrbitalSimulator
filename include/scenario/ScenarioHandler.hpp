#pragma once
#include <string>

struct Scenario;

class ScenarioHandler
{
public:
	explicit ScenarioHandler(const Scenario& scenario) : m_scenario{ scenario } {}
	void handleScenario() const;
private:
	void runSimulationForScenario() const;
	void saveScenario() const;
	void saveScenario(const std::string& saveName) const;
	const Scenario& m_scenario;
};
