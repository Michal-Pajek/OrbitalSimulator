#pragma once
#include <string>
#include "math/Vector2D.hpp"

class Body
{
public:
	Body() = delete;
	Body(const std::string& name, double mass, const Vector2D& pos, const Vector2D& vel) : m_name{ name }, m_mass{ mass }, m_position{ pos }, m_velocity{ vel }/*, m_id{++s_ids}*/ {}
	void resetForce() { m_force = {}; }
	void increaseGravityForce(const Vector2D& force) { m_force += force; }
	void calculateAcceleration() { m_acceleration = m_force / m_mass; }
	void calculateNextPosition(const double dt);
	void applyStep();
	void debugPrint() const;
	const Vector2D& getPosition() const { return m_position; }
	double getMass() const { return m_mass; }
private:
	//const unsigned int m_id;
	const std::string m_name;
	const double m_mass;
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_force{};
	Vector2D m_acceleration{};
	Vector2D m_newPos{};
	Vector2D m_newVel{};
	//static unsigned int s_ids{};
};

Vector2D getGravityForceBetween(const Body& a, const Body& b);