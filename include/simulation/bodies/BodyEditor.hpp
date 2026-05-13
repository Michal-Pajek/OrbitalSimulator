#pragma once
#include "Body.hpp"

class BodyEditor
{
public:
	BodyEditor(Body body, const std::vector<Body>& bodies) : m_body{ std::move(body) }, m_bodies { bodies } {}
	BodyEditor() = delete;
	void editBody();
	Body getBody() { return std::move(m_body); }
private:
	bool isBodyNameAlreadyUsed(const std::string& checkedName) const;
	bool isBodyPositionAlreadyUsed(const Vector3D& position) const;
	double promptForBodyMass() const;
	double promptForBodyMass(const BodyTypeImpl::MassInterval& massInterval) const;
	std::string promptForBodyName() const;
	BodyType promptForBodyType() const;
	Vector3D promptForBodyPosition() const;
	Vector3D promptForBodyVelocity() const;
	Body m_body;
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