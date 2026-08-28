#include "body/input/BodyEditor.hpp"

#include "body/types/BodyTypeCatalog.hpp"

#include "input/core/Console.hpp"
#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"
#include "ui/menu/Menu.hpp"

namespace body::input
{
	void BodyEditor::editBody()
	{
		::input::console::clearScreen();
		ConsoleWriter::writeLine(localization::TextId::YouAreEditingBody, ' ', m_body.getName());
		const Menu whatToChangeInBody{ {
				MenuOption{'N', localization::TextId::BodyName,		[this]() {m_body.setName(promptForBodyName()); }},
				MenuOption{'T', localization::TextId::BodyType,		[this]() {
					const auto newTypeId{ promptForBodyType() };
					const auto newMass{ resolveMassForTypeChange(newTypeId) };
					m_body.setTypeAndMass(newTypeId, newMass);
				}},
				MenuOption{'M', localization::TextId::BodyMass,		[this]() {m_body.setMass(promptForBodyMass()); }},
				MenuOption{'P', localization::TextId::BodyPosition,	[this]() {m_body.setPosition(promptForBodyPosition()); }},
				MenuOption{'V', localization::TextId::BodyVelocity,	[this]() {m_body.setVelocity(promptForBodyVelocity()); }},
				MenuOption{'B', localization::TextId::Back,			[]() {}}},
				localization::TextId::QuestionWhatDoYouWantToChangeInBody };
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
			ConsoleWriter::writeLine(localization::TextId::BodyMassOutOfInterval);
			return promptForBodyMass(newTypeId);
		}

		ConsoleWriter::writeLine(localization::TextId::CurrentBodyMassIsWithinTheRangeForThisType);

		if (!Menu::yesOrNo(localization::TextId::QuestionDoYouStillWantToEnterNewValue)) {
			return currentMass;
		}

		return promptForBodyMass(newTypeId);
	}
} // namespace body::input
