#pragma once
#include <string>
#include <vector>

#include "simulation/bodies/Body.hpp"

#include "simulation/bodies/types/BodyType.hpp"

#include "math/Vector3D.hpp"

class BodyInputBase
{
public:
	BodyInputBase(const std::vector<Body>& bodies) : m_bodies{ bodies } {}
	BodyInputBase() = delete;
protected:
	bool isBodyNameAlreadyUsed(const std::string& checkedName) const;
	bool isBodyPositionAlreadyUsed(const Vector3D& position) const;
	double promptForBodyMass(const BodyTypeId bodyTypeId) const;
	std::string promptForBodyName() const;
	BodyTypeId promptForBodyType() const;
	Vector3D promptForBodyPosition() const;
	Vector3D promptForBodyVelocity() const;
	virtual bool isSameAsCurrentName(const std::string& enteredName) const = 0;
	virtual bool isSameAsCurrentPosition(const Vector3D& enteredPosition) const = 0;
	const std::vector<Body>& m_bodies;

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
