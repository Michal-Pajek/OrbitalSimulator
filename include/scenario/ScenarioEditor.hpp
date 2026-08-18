#pragma once
#include <optional>
#include <utility>
#include "Scenario.hpp"

class ScenarioEditor
{
public:
	explicit ScenarioEditor(Scenario scenario) : m_scenario{ std::move(scenario) } {}
	std::optional<Scenario> getReviewedScenario();
private:
	void printBodies() const;
	void reviewAndEditBodies();
	void reviseScenario();
	Scenario m_scenario;
};
