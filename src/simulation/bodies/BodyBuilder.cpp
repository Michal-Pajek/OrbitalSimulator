#include "simulation/bodies/BodyBuilder.hpp"
#include <stdexcept>
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/DataGetter.hpp"
#include "localization/TextId.hpp"
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
	const auto bodyMass{ promptForBodyMass() };
	const auto bodyPosition{ promptForBodyPosition() };
	const auto bodyVelocity{ promptForBodyVelocity() };

	Body result{ bodyName, bodyType, bodyMass, bodyPosition, bodyVelocity };

	reviewAndEditBody(result);

	return result;
}

void BodyBuilder::editBody(Body& body) const
{
	clearScreen();
	ConsoleWriter::writeLine(TextId::YouAreEditingBody, ' ', body.getName());
	const Menu whatToChangeInBody{ {
			MenuOption{'N', TextId::BodyName,		[&body, this]() {body.setName(promptForBodyName(body.getName())); }},
			MenuOption{'M', TextId::BodyMass,		[&body, this]() {body.setMass(promptForBodyMass()); }},
			MenuOption{'P', TextId::BodyPosition,	[&body, this]() {body.setPosition(promptForBodyPosition(body.getPosition())); }},
			MenuOption{'V', TextId::BodyVelocity,	[&body, this]() {body.setVelocity(promptForBodyVelocity()); }},
			MenuOption{'B', TextId::Back,			[]() {}}},
			TextId::QuestionWhatDoYouWantToChangeInBody };
	whatToChangeInBody.execute();
}

bool BodyBuilder::isBodyNameAlreadyUsed(const std::string& checkedName) const
{
	return doesAnyBodyMatch([&checkedName](const Body& body) {return body.getName() == checkedName; });
}

bool BodyBuilder::isBodyPositionAlreadyUsed(const Vector3D& position) const
{
	return doesAnyBodyMatch([&position](const Body& body) {return body.getPosition() == position; });
}

double BodyBuilder::promptForBodyMass() const
{
	ConsoleWriter::writeLine();
	const auto massMultiplier{ getUnitMultiplier(std::vector<MenuOptionPair>{
		{TextId::Kilogram,	1.0},
		{TextId::Ton,		physics::TON},
		{TextId::Kiloton,	physics::KILOTON},
		{TextId::Megaton,	physics::MEGATON},
		{TextId::EarthMass, physics::EARTH_MASS},
		{TextId::SolarMass, physics::SOLAR_MASS}},
		TextId::SelectMassUnit) };
	ConsoleWriter::write(TextId::EnterBodyMass, ": ");

	return massMultiplier * DataGetter::getValue<double>([](const double x) {return x > 0.0; });
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

		editBody(body);
	}
}

std::string BodyBuilder::promptForBodyName(const std::optional<std::string>& currentName) const
{
	ConsoleWriter::write(TextId::EnterOneWordName, ": ");
	auto enteredName{ DataGetter::getSingleWordText() };
	if (currentName && *currentName == enteredName) {
		return enteredName;
	}
	while (isBodyNameAlreadyUsed(enteredName)) {
		ConsoleWriter::write(TextId::BodyNameAlreadyUsedEnterAnother, ": ");
		enteredName = DataGetter::getSingleWordText();
	}
	return enteredName;
}

BodyType BodyBuilder::promptForBodyType() const
{
	BodyType result{};
	const Menu selectBodyType{ {
		MenuOption{'T', TextId::Custom,			[]() {}},
		MenuOption{'M', TextId::Meteor,			[&result]() {result = BodyType::Meteor; }},
		MenuOption{'A', TextId::Asteroid,		[&result]() {result = BodyType::Asteroid; }},
		MenuOption{'C', TextId::Comet,			[&result]() {result = BodyType::Comet; }},
		MenuOption{'D', TextId::DwarfPlanet,	[&result]() {result = BodyType::DwarfPlanet; }},
		MenuOption{'P', TextId::Planet,			[&result]() {result = BodyType::Planet; }},
		MenuOption{'B', TextId::BrownDwarf,		[&result]() {result = BodyType::BrownDwarf; }},
		MenuOption{'S', TextId::Star,			[&result]() {result = BodyType::Star; }}},
		TextId::SelectBodyType };
	selectBodyType.execute();
	return result;
}

Vector3D BodyBuilder::promptForBodyPosition(const std::optional<Vector3D>& currentPosition) const
{
	ConsoleWriter::writeLine();
	const auto distanceMultiplier{ getUnitMultiplier(std::vector<MenuOptionPair>{
		{TextId::Metre,							1.0},
		{TextId::Kilometre,						physics::KM_MULTIPLIER},
		{TextId::ThousandKilometre,				physics::KKM_MULTIPLIER},
		{TextId::MillionKilometre,				physics::MKM_MULTIPLIER},
		{TextId::AstronomicalUnit,				physics::AU},
		{TextId::AverageEarthToMoonDistance,	physics::EARTH_MOON_DISTANCE}},
		TextId::SelectDistanceUnit) };

	ConsoleWriter::write(TextId::EnterPositionVector, ": ");
	auto enteredPosition{ distanceMultiplier * DataGetter::getVector3D() };
	if (currentPosition && *currentPosition == enteredPosition) {
		return enteredPosition;
	}
	while (isBodyPositionAlreadyUsed(enteredPosition)) {
		ConsoleWriter::write(TextId::BodyPositionAlreadyOccupiedEnterAnother, ": ");
		enteredPosition = distanceMultiplier * DataGetter::getVector3D();
	}
	return enteredPosition;
}

Vector3D BodyBuilder::promptForBodyVelocity() const
{
	ConsoleWriter::writeLine();
	const auto velocityMultiplier{ getUnitMultiplier(std::vector<MenuOptionPair>{
		{TextId::MetrePerSecond, 1.0},
		{TextId::KilometrePerSecond, physics::KMS_MULTIPLIER},
		{TextId::ThousandKilometrePerHour, physics::KKMH_MULTIPLIER},
		{TextId::SpeedOfLight, physics::C_CONST}},
		TextId::SelectSpeedUnit) };

	ConsoleWriter::write(TextId::EnterVelocityVector, ": ");
	return velocityMultiplier * DataGetter::getVector3D([velocityMultiplier](const double v) {return std::abs(velocityMultiplier * v) < physics::C_CONST; });
}
