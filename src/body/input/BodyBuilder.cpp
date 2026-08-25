#include "body/input/BodyBuilder.hpp"

#include <utility>

#include "body/input/BodyEditor.hpp"

#include "input/core/Console.hpp"
#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"
#include "ui/menu/Menu.hpp"

Body BodyBuilder::createBodyFromInput() const
{
	Console::clearScreen();
	ConsoleWriter::writeHeadline(TextId::EnterNewBodyData);
	const auto bodyName{ promptForBodyName() };
	const auto bodyType{ promptForBodyType() };
	const auto bodyMass{ promptForBodyMass(bodyType) };
	const auto bodyPosition{ promptForBodyPosition() };
	const auto bodyVelocity{ promptForBodyVelocity() };

	Body result{ bodyName, bodyType, bodyMass, bodyPosition, bodyVelocity };

	reviewAndEditBody(result);

	return result;
}

void BodyBuilder::reviewAndEditBody(Body& body) const
{
	Console::clearScreen();
	ConsoleWriter::writeHeadline(TextId::ConfirmBody);
	while (true) {
		body.printSummary();
		ConsoleWriter::writeLine();
		if (Menu::yesOrNo(TextId::QuestionDoYouWantToAccept)) {
			return;
		}

		BodyEditor bodyEditor{ std::move(body), m_bodies };
		bodyEditor.editBody();
		body = bodyEditor.takeBody();
	}
}
