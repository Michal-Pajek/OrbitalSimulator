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
		ui::console::writeLine(localization::TextId::YouAreEditingBody, ' ', m_body.getName());
		const ui::Menu whatToChangeInBody{ {
				ui::MenuOption{'N', localization::TextId::BodyName,		[this]() {m_body.setName(promptForBodyName()); }},
				ui::MenuOption{'T', localization::TextId::BodyType,		[this]() {
					const auto newTypeId{ promptForBodyType() };
					const auto newMass{ resolveMassForTypeChange(newTypeId) };
					m_body.setTypeAndMass(newTypeId, newMass);
				}},
				ui::MenuOption{'M', localization::TextId::BodyMass,		[this]() {m_body.setMass(promptForBodyMass()); }},
				ui::MenuOption{'P', localization::TextId::BodyPosition,	[this]() {m_body.setPosition(promptForBodyPosition()); }},
				ui::MenuOption{'V', localization::TextId::BodyVelocity,	[this]() {m_body.setVelocity(promptForBodyVelocity()); }},
				ui::MenuOption{'B', localization::TextId::Back,			[]() {}}},
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
			ui::console::writeLine(localization::TextId::BodyMassOutOfInterval);
			return promptForBodyMass(newTypeId);
		}

		ui::console::writeLine(localization::TextId::CurrentBodyMassIsWithinTheRangeForThisType);

		if (!ui::Menu::yesOrNo(localization::TextId::QuestionDoYouStillWantToEnterNewValue)) {
			return currentMass;
		}

		return promptForBodyMass(newTypeId);
	}
} // namespace body::input
