#pragma once
#include <string>

#include "body/types/BodyType.hpp"

#include "math/Vector3D.hpp"

namespace body
{
	class Body
	{
	public:
		Body(const std::string& name, BodyTypeId typeId, double mass, const math::Vector3D& position, const math::Vector3D& velocity);
		double getMass() const { return m_mass; }
		const math::Vector3D& getPosition() const { return m_position; }
		const math::Vector3D& getVelocity() const { return m_velocity; }
		BodyTypeId getTypeId() const { return m_typeId; }
		void printSummary(const bool oneLine = false) const;
		void setMass(const double mass);
		void setName(const std::string& name) { m_name = name; }
		void setPosition(const math::Vector3D& position) { m_position = position; }
		void setTypeAndMass(const BodyTypeId typeId, const double mass);
		void setVelocity(const math::Vector3D& velocity);
		const std::string& getName() const { return m_name; }
	private:
		std::string m_name;
		BodyTypeId m_typeId;
		double m_mass;
		math::Vector3D m_position;
		math::Vector3D m_velocity;
	};
} // namespace body
