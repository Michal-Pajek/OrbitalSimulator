#pragma once
#include <string>
#include "BodyType.hpp"
#include "math/Vector3D.hpp"

class Body
{
public:
	Body() = delete;
	Body(const std::string& name, BodyType bodyType, double mass, const Vector3D& position, const Vector3D& velocity);
	double getMass() const { return m_mass; }
	const Vector3D& getPosition() const { return m_position; }
	const Vector3D& getVelocity() const { return m_velocity; }
	BodyType getType() const { return m_bodyType; }
	void printSummary(const bool oneLine = false) const;
	void setMass(const double mass);
	void setName(const std::string& name) { m_name = name; }
	void setPosition(const Vector3D& position) { m_position = position; }
	void setType(const BodyType bodyType) { m_bodyType = bodyType; }
	void setVelocity(const Vector3D& velocity) { m_velocity = velocity; }
	const std::string& getName() const { return m_name; }
private:
	std::string m_name;
	double m_mass;
	BodyType m_bodyType;
	Vector3D m_position;
	Vector3D m_velocity;
};

Vector3D getGravityForceBetween(const Body& a, const Body& b);