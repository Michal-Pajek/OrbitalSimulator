#pragma once
#include <string>
#include <vector>
#include "Body.hpp"
#include "BodyType.hpp"
#include "math/Vector3D.hpp"

class BodyBuilderEditorInterface
{
public:
	BodyBuilderEditorInterface(const std::vector<Body>& bodies) : m_bodies{ bodies } {}
	BodyBuilderEditorInterface() = delete;
protected:
	bool isBodyNameAlreadyUsed(const std::string& checkedName) const;
	bool isBodyPositionAlreadyUsed(const Vector3D& position) const;
	double promptForBodyMass(const BodyTypeImpl::MassInterval& massInterval) const;
	std::string promptForBodyName() const;
	BodyType promptForBodyType() const;
	Vector3D promptForBodyPosition() const;
	Vector3D promptForBodyVelocity() const;
	virtual bool isTheSameNameAsBefore(const std::string& enteredName) const = 0;
	virtual bool isTheSamePositionAsBefore(const Vector3D& enteredPosition) const = 0;
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