#pragma once
#include <string>
#include "math/Vector2D.hpp"

class Body
{
public:
	Body() = delete;
	Body(const std::string& name, double mass, const Vector2D& pos, const Vector2D& vel);
	double getMass() const { return m_mass; }
	const Vector2D& getPosition() const { return m_position; }
	const Vector2D& getVelocity() const { return m_velocity; }
	void setPosition(const Vector2D& position) { m_position = position; }
	void setVelocity(const Vector2D& velocity) { m_velocity = velocity; }
	const std::string& getName() const { return m_name; }
private:
	std::string m_name;
	double m_mass;
	Vector2D m_position;
	Vector2D m_velocity;
};

Vector2D getGravityForceBetween(const Body& a, const Body& b);