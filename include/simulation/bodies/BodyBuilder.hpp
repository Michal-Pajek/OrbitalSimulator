#pragma once
#include <vector>
#include "Body.hpp"
#include "BodyBuilderEditorInterface.hpp"
#include "math/Vector3D.hpp"

class BodyBuilder : public BodyBuilderEditorInterface
{
public:
	BodyBuilder(const std::vector<Body>& bodies) : BodyBuilderEditorInterface{ bodies } {}
	BodyBuilder() = delete;
	Body createBodyFromInput() const;
private:
	bool isTheSameNameAsBefore(const std::string& enteredName) const override { return false; }
	bool isTheSamePositionAsBefore(const Vector3D& enteredPosition) const override { return false; }
	void reviewAndEditBody(Body& body) const;
};