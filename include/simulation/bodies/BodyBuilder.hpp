#pragma once
#include <optional>
#include <vector>
#include "Body.hpp"
#include "math/Vector3D.hpp"

class BodyBuilder
{
public:
	BodyBuilder(const std::vector<Body>& bodies) : m_bodies{ bodies } {}
	BodyBuilder() = delete;
	Body createBodyFromInput() const;
	void editBody(Body& body) const;
private:
	bool isBodyNameAlreadyUsed(const std::string& checkedName) const;
	bool isBodyPositionAlreadyUsed(const Vector3D& position) const;
	double promptForBodyMass() const;
	void reviewAndEditBody(Body& body) const;
	std::string promptForBodyName(const std::optional<std::string>& currentName = std::nullopt) const;
	Vector3D promptForBodyPosition(const std::optional<Vector3D>& currentPosition = std::nullopt) const;
	Vector3D promptForBodyVelocity() const;
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