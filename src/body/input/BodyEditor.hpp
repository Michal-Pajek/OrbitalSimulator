#pragma once
#include <string>
#include <utility>
#include <vector>

#include "body/input/BodyInputBase.hpp"

#include "body/Body.hpp"
#include "body/types/BodyType.hpp"

#include "math/Vector3D.hpp"

namespace body::input
{
	class BodyEditor : public BodyInputBase
	{
	public:
		BodyEditor(Body body, const std::vector<Body>& bodies)
			: BodyInputBase{ bodies }, m_body{ std::move(body) } {
		}
		void editBody();
		Body takeBody() { return std::move(m_body); }
	private:
		using BodyInputBase::promptForBodyMass;
		bool isSameAsCurrentName(const std::string& enteredName) const override { return m_body.getName() == enteredName; }
		bool isSameAsCurrentPosition(const math::Vector3D& enteredPosition) const override { return m_body.getPosition() == enteredPosition; }
		double promptForBodyMass() const;
		double resolveMassForTypeChange(const BodyTypeId newTypeId);
		Body m_body;
	};
} // namespace body::input
