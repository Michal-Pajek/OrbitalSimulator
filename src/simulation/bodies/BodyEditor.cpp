#include "simulation/bodies/BodyEditor.hpp"
#include "app/Menu.hpp"
#include "input/Console.hpp"
#include "input/DataGetter.hpp"
#include "ui/ConsoleWriter.hpp"

void BodyEditor::editBody()
{
	clearScreen();
	ConsoleWriter::writeLine(TextId::YouAreEditingBody, ' ', m_body.getName());
	const Menu whatToChangeInBody{ {
			MenuOption{'N', TextId::BodyName,		[this]() {m_body.setName(promptForBodyName()); }},
			MenuOption{'T', TextId::BodyType,		[this]() {m_body.setType(promptForBodyType()); }},
			MenuOption{'M', TextId::BodyMass,		[this]() {m_body.setMass(promptForBodyMass()); }},
			MenuOption{'P', TextId::BodyPosition,	[this]() {m_body.setPosition(promptForBodyPosition()); }},
			MenuOption{'V', TextId::BodyVelocity,	[this]() {m_body.setVelocity(promptForBodyVelocity()); }},
			MenuOption{'B', TextId::Back,			[]() {}}},
			TextId::QuestionWhatDoYouWantToChangeInBody };
	whatToChangeInBody.execute();
}

bool BodyEditor::isBodyNameAlreadyUsed(const std::string& checkedName) const
{
	return doesAnyBodyMatch([&checkedName](const Body& body) {return body.getName() == checkedName; });
}

bool BodyEditor::isBodyPositionAlreadyUsed(const Vector3D& position) const
{
	return doesAnyBodyMatch([&position](const Body& body) {return body.getPosition() == position; });
}

double BodyEditor::promptForBodyMass() const
{
	return promptForBodyMass(BodyTypeImpl::getInterval(m_body.getType()));
}

double BodyEditor::promptForBodyMass(const BodyTypeImpl::MassInterval& massInterval) const
{
	ConsoleWriter::writeLine();
	const auto massMultiplier{ getUnitMultiplier(BodyTypeImpl::getMassUnitVector(massInterval), TextId::SelectMassUnit) };
	const auto min{ massInterval.min / massMultiplier };
	const auto max{ massInterval.max / massMultiplier };
	ConsoleWriter::write(TextId::EnterBodyMass, " (", TextId::Interval, ' ', min, " - ", max, "): ");

	return massMultiplier * DataGetter::getValue<double>([min, max](const double x) {return x >= min && x <= max; });
}

std::string BodyEditor::promptForBodyName() const
{
	ConsoleWriter::write(TextId::EnterOneWordName, ": ");
	auto enteredName{ DataGetter::getSingleWordText() };
	if (m_body.getName() == enteredName) {
		return enteredName;
	}
	while (isBodyNameAlreadyUsed(enteredName)) {
		ConsoleWriter::write(TextId::BodyNameAlreadyUsedEnterAnother, ": ");
		enteredName = DataGetter::getSingleWordText();
	}
	return enteredName;
}

BodyType BodyEditor::promptForBodyType() const
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
	// --------------------
	// todo - zmiana masy jeśli nie pasuje do przedziału
	// --------------------
	return result;
}

Vector3D BodyEditor::promptForBodyPosition() const
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
	if (m_body.getPosition() == enteredPosition) {
		return enteredPosition;
	}
	while (isBodyPositionAlreadyUsed(enteredPosition)) {
		ConsoleWriter::write(TextId::BodyPositionAlreadyOccupiedEnterAnother, ": ");
		enteredPosition = distanceMultiplier * DataGetter::getVector3D();
	}
	return enteredPosition;
}

Vector3D BodyEditor::promptForBodyVelocity() const
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
