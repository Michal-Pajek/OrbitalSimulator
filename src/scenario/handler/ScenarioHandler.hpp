#pragma once
#include <string>

struct Scenario;

struct ScenarioHandlingConfig
{
	bool askToRun{ true };
	bool askToSave{ true };
	bool printSummary{ true };
};

class ScenarioHandler
{
public:
	static void buildAndHandleScenario();
	static void loadAndHandleScenario();
	explicit ScenarioHandler(const Scenario& scenario) : m_scenario{ scenario } {}
	void handleScenario(const ScenarioHandlingConfig& config = {}) const;
private:
	void runSimulationForScenario() const;
	void saveScenario() const;
	void saveScenario(const std::string& saveName) const;
	const Scenario& m_scenario;
};
