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
	bool handleBodiesMenu();
	void addNewBody();
	void deleteSelectedBody();
	void editSelectedBody();
	void handleEmptyBodies();
	void printBodies() const;
	void reviewAndEditBodies();
	void reviseScenario();
	std::size_t promptForBodyIdx() const;
	Scenario m_scenario;
};
