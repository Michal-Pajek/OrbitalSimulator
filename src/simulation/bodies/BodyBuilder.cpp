#include "simulation/bodies/BodyBuilder.hpp"
#include <utility>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "localization/TextId.hpp"
#include "simulation/bodies/BodyEditor.hpp"
#include "ui/ConsoleWriter.hpp"

Body BodyBuilder::createBodyFromInput() const
{
	clearScreen();
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
	clearScreen();
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
