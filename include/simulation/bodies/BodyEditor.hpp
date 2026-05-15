#pragma once
#include <utility>
#include <vector>
#include "Body.hpp"
#include "BodyBuilderEditorInterface.hpp"

class BodyEditor : public BodyBuilderEditorInterface
{
public:
	BodyEditor(Body body, const std::vector<Body>& bodies) : BodyBuilderEditorInterface{ bodies }, m_body { std::move(body) } {}
	BodyEditor() = delete;
	void editBody();
	Body getBody() { return std::move(m_body); }
private:
	using BodyBuilderEditorInterface::promptForBodyMass;
	bool isTheSameNameAsBefore(const std::string& enteredName) const override { return m_body.getName() == enteredName; }
	bool isTheSamePositionAsBefore(const Vector3D& enteredPosition) const override { return m_body.getPosition() == enteredPosition; }
	double promptForBodyMass() const;
	void changeMassIfIsOutOfInterval();
	Body m_body;
};