#pragma once
#include <string>
#include <vector>

#include "body/input/BodyInputBase.hpp"

#include "body/Body.hpp"

#include "math/Vector3D.hpp"

namespace body::input
{
	class BodyBuilder : public BodyInputBase
	{
	public:
		explicit BodyBuilder(const std::vector<Body>& bodies) : BodyInputBase{ bodies } {}
		Body createBodyFromInput() const;
	private:
		bool isSameAsCurrentName(const std::string& enteredName) const override { return false; }
		bool isSameAsCurrentPosition(const math::Vector3D& enteredPosition) const override { return false; }
		void reviewAndEditBody(Body& body) const;
	};
} // namespace body::input
