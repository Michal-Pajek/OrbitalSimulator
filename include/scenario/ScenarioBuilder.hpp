#pragma once
#include <optional>
#include <string>
#include <vector>
#include "scenario/Scenario.hpp"
#include "simulation/Body.hpp"

class ScenarioBuilder
{
public:
	ScenarioBuilder() = default;
	std::optional<Scenario> buildScenario();
private:
	bool isBodyNameAlreadyUsed(const std::string& checkedName) const;
	bool isBodyPositionAlreadyUsed(const Vector3D& position) const;
	bool reviewAndConfirmScenario();
	double promptForBodyMass() const;
	void createBodiesFromInput();
	void editBody(Body& body);
	void printBodies(const bool printHeadline = true) const;
	void printScenarioSummary() const;
	void promptForScenarioName();
	void promptForStepCount();
	void promptForTimeStep();
	void resetState();
	void reviewAndEditBodies();
	void reviewAndEditBody(Body& body);
	void reviseScenario();
	std::string promptForBodyName(const std::optional<std::string>& currentName = std::nullopt) const;
	Body createBodyFromInput();
	Vector3D promptForBodyPosition(const std::optional<Vector3D>& currentPosition = std::nullopt) const;
	Vector3D promptForBodyVelocity() const;
	double m_timeStep{};
	unsigned int m_stepCount{};
	std::string m_name{};
	std::vector<Body> m_bodies{};

	template <typename Predicate>
	bool doesAnyBodyMatch(const Predicate& predicate) const
	{
		for (const auto& body : m_bodies) {
			if (predicate(body)) {
				return true;
			}
		}
		return false;
	}
};