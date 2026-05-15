#include "simulation/bodies/BodyBuilder.hpp"
#include <stdexcept>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "localization/TextId.hpp"
#include "simulation/bodies/BodyEditor.hpp"
#include "ui/ConsoleWriter.hpp"

namespace
{
	//struct MenuOptionPair {
	//	TextId textId;
	//	double multiplier;
	//	MenuOptionPair() = delete;
	//	MenuOptionPair(TextId _textId, double _multiplier) : textId{ _textId }, multiplier{ _multiplier } {}
	//};

	//double getUnitMultiplier(const std::vector<MenuOptionPair>& options, const TextId menuTitle)
	//{
	//	const auto size{ options.size() };
	//	if (size == 0 || size >= 10u) {
	//		throw std::invalid_argument("Options vector in getUnitMultiplier must be between 1 and 9");
	//	}

	//	double result{};
	//	TextId selectedUnit;
	//	auto key{ '1' };
	//	std::vector<MenuOption> menuOptions{};
	//	menuOptions.reserve(size);
	//	for (size_t idx{}; idx < size; ++idx) {
	//		const auto& multiplier{ options.at(idx).multiplier };
	//		const auto& textId{ options.at(idx).textId };
	//		menuOptions.emplace_back(key++, textId, [&result, &selectedUnit, multiplier, textId]() {result = multiplier; selectedUnit = textId; });
	//	}

	//	const Menu selectUnitMenu{ menuOptions, menuTitle };
	//	selectUnitMenu.execute();
	//	ConsoleWriter::writeLine(TextId::SelectedUnit, ": ", selectedUnit);
	//	return result;
	//}
} // anonymous namespace

Body BodyBuilder::createBodyFromInput() const
{
	clearScreen();
	ConsoleWriter::writeHeadline(TextId::EnterNewBodyData);
	const auto bodyName{ promptForBodyName() };
	const auto bodyType{ promptForBodyType() };
	const auto bodyMass{ promptForBodyMass(BodyTypeImpl::getInterval(bodyType)) };
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

		BodyEditor bodyEditor{ body, m_bodies };
		bodyEditor.editBody();
		body = bodyEditor.getBody();
	}
}