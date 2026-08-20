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
	bool canAddBody() const { return m_scenario.bodies.size() < Scenario::MAX_BODY_COUNT; }
	bool handleBodiesMenu();
	void addNewBody();
	void deleteSelectedBody();
	void editSelectedBody();
	void ensureAtLeastOneBody();
	void printBodies() const;
	void reviewAndEditBodies();
	void reviseScenario();
	std::size_t promptForBodyIdx() const;
	Scenario m_scenario;
};
