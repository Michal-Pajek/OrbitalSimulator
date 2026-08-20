#include "simulation/bodies/BodyEditor.hpp"

#include "simulation/bodies/types/BodyTypeCatalog.hpp"

#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "localization/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

void BodyEditor::editBody()
{
	Console::clearScreen();
	ConsoleWriter::writeLine(TextId::YouAreEditingBody, ' ', m_body.getName());
	const Menu whatToChangeInBody{ {
			MenuOption{'N', TextId::BodyName,		[this]() {m_body.setName(promptForBodyName()); }},
			MenuOption{'T', TextId::BodyType,		[this]() {
				const auto newTypeId{ promptForBodyType() };
				const auto newMass{ resolveMassForTypeChange(newTypeId) };
				m_body.setTypeAndMass(newTypeId, newMass);
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
	return promptForBodyMass(m_body.getTypeId());
}

double BodyEditor::resolveMassForTypeChange(const BodyTypeId newTypeId)
{
	const auto currentMass{ m_body.getMass() };

	if (!BodyTypeCatalog::isMassInRange(newTypeId, currentMass)) {
		ConsoleWriter::writeLine(TextId::BodyMassOutOfInterval);
		return promptForBodyMass(newTypeId);
	}

	ConsoleWriter::writeLine(TextId::CurrentBodyMassIsWithinTheRangeForThisType);

	if (!Menu::yesOrNo(TextId::QuestionDoYouStillWantToEnterNewValue)) {
		return currentMass;
	}

	return promptForBodyMass(newTypeId);
}
