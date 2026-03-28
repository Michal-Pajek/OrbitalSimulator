#pragma once
#include <vector>
#include "simulation/Body.hpp"

class Simulation
{
	class BodyStepState;
public:
	Simulation() = delete;
	Simulation(const std::vector<Body>& bodies);
	Simulation(const std::vector<Body>& bodies, const double dt);
	void step();
	void setBodies(const std::vector<Body>& bodies);
	void setDt(const double dt);
	double getDt() const { return m_dt; }
	double getTime() const { return m_time; }
	size_t getBodyCount() const { return m_bodyStepStates.size(); }
	const Body& getBody(const size_t idx) const;
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
	BodyStepState(const Body& body) : m_body{ body } {}
	void applyStep();
	void increaseGravityForce(const Vector2D& force) { m_force += force; }
	void calculateAcceleration() { m_acceleration = m_force / m_body.getMass(); }
	void calculateNextPosition(const double dt);
	void resetForce() { m_force = {}; }
	const Body& getBody() const { return m_body; }
private:
	Body m_body;
	Vector2D m_acceleration{};
	Vector2D m_force{};
	Vector2D m_newPos{};
	Vector2D m_newVel{};
};