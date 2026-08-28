#pragma once
#include <vector>

#include "body/Body.hpp"
#include "math/Vector3D.hpp"

class Simulation
{
	class BodyStepState;
public:
	Simulation() = delete;
	Simulation(const std::vector<body::Body>& bodies);
	Simulation(const std::vector<body::Body>& bodies, const double dt);
	void runSteps(const unsigned int n);
	void step();
	void setBodies(const std::vector<body::Body>& bodies);
	void setDt(const double dt);
	double getDt() const { return m_dt; }
	double getTime() const { return m_time; }
	size_t getBodyCount() const { return m_bodyStepStates.size(); }
	const body::Body& getBody(const size_t idx) const;
private:
	void applyStepForAllBodies();
	void calculateForcesBetweenBodies();
	void calculateNextStates();
	void resetForceForAllBodies();
	std::vector<BodyStepState> m_bodyStepStates;
	double m_dt{ 1.0 };
	double m_time{};
};

class Simulation::BodyStepState
{
public:
	BodyStepState(const body::Body& body) : m_body{ body } {}
	void applyStep();
	void calculateAcceleration() { m_acceleration = m_force / m_body.getMass(); }
	void calculateNextPosition(const double dt);
	void increaseGravityForce(const math::Vector3D& force) { m_force += force; }
	void resetForce() { m_force = {}; }
	const body::Body& getBody() const { return m_body; }
private:
	body::Body m_body;
	math::Vector3D m_acceleration{};
	math::Vector3D m_force{};
	math::Vector3D m_newPos{};
	math::Vector3D m_newVel{};
};
