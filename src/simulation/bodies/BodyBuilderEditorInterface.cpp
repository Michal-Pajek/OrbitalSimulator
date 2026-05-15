#include "simulation/bodies/BodyBuilderEditorInterface.hpp"
#include "input/DataGetter.hpp"

bool BodyBuilderEditorInterface::isBodyNameAlreadyUsed(const std::string& checkedName) const
{
	return doesAnyBodyMatch([&checkedName](const Body& body) {return body.getName() == checkedName; });
}

bool BodyBuilderEditorInterface::isBodyPositionAlreadyUsed(const Vector3D& position) const
{
	return doesAnyBodyMatch([&position](const Body& body) {return body.getPosition() == position; });
}

double BodyBuilderEditorInterface::promptForBodyMass(const BodyTypeImpl::MassInterval& massInterval) const
{
	ConsoleWriter::writeLine();
	const auto massMultiplier{ getUnitMultiplier(BodyTypeImpl::getMassUnitVector(massInterval), TextId::SelectMassUnit) };
	const auto min{ massInterval.min / massMultiplier };
	const auto max{ massInterval.max / massMultiplier };
	ConsoleWriter::write(TextId::EnterBodyMass, " (", TextId::Interval, ' ', min, " - ", max, "): ");

	return massMultiplier * DataGetter::getValue<double>([min, max](const double x) {return x >= min && x <= max; });
}

std::string BodyBuilderEditorInterface::promptForBodyName() const
{
	ConsoleWriter::write(TextId::EnterOneWordName, ": ");
	auto enteredName{ DataGetter::getSingleWordText() };
	if (isTheSameNameAsBefore(enteredName)) {
		return enteredName;
	}
	while (isBodyNameAlreadyUsed(enteredName)) {
		ConsoleWriter::write(TextId::BodyNameAlreadyUsedEnterAnother, ": ");
		enteredName = DataGetter::getSingleWordText();
	}
	return enteredName;
}

BodyType BodyBuilderEditorInterface::promptForBodyType() const
{
	BodyType result{};
	const Menu selectBodyType{ {
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

Vector3D BodyBuilderEditorInterface::promptForBodyPosition() const
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
	if (isTheSamePositionAsBefore(enteredPosition)) {
		return enteredPosition;
	}
	while (isBodyPositionAlreadyUsed(enteredPosition)) {
		ConsoleWriter::write(TextId::BodyPositionAlreadyOccupiedEnterAnother, ": ");
		enteredPosition = distanceMultiplier * DataGetter::getVector3D();
	}
	return enteredPosition;
}

Vector3D BodyBuilderEditorInterface::promptForBodyVelocity() const
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
