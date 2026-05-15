#include "simulation/bodies/BodyEditor.hpp"
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "ui/ConsoleWriter.hpp"

void BodyEditor::editBody()
{
	clearScreen();
	ConsoleWriter::writeLine(TextId::YouAreEditingBody, ' ', m_body.getName());
	const Menu whatToChangeInBody{ {
			MenuOption{'N', TextId::BodyName,		[this]() {m_body.setName(promptForBodyName()); }},
			MenuOption{'T', TextId::BodyType,		[this]() {
				m_body.setType(promptForBodyType());
				changeMassIfIsOutOfInterval();
			}},
			MenuOption{'M', TextId::BodyMass,		[this]() {m_body.setMass(promptForBodyMass()); }},
			MenuOption{'P', TextId::BodyPosition,	[this]() {m_body.setPosition(promptForBodyPosition()); }},
			MenuOption{'V', TextId::BodyVelocity,	[this]() {m_body.setVelocity(promptForBodyVelocity()); }},
			MenuOption{'B', TextId::Back,			[]() {}}},
			TextId::QuestionWhatDoYouWantToChangeInBody };
	whatToChangeInBody.execute();
}

double BodyEditor::promptForBodyMass() const
{
	return promptForBodyMass(BodyTypeImpl::getInterval(m_body.getType()));
}

void BodyEditor::changeMassIfIsOutOfInterval()
{
	const auto currentMass{ m_body.getMass() };
	const auto type{ m_body.getType() };
	const auto min{ BodyTypeImpl::getInterval(type).min };
	const auto max{ BodyTypeImpl::getInterval(type).max };
	if (currentMass < min || currentMass > max) {
		ConsoleWriter::writeLine(TextId::BodyMassOutOfInterval);
		promptForBodyMass();
	}
}
