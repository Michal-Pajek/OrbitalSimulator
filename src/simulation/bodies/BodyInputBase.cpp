#include "simulation/bodies/BodyInputBase.hpp"
#include <cmath>
#include "input/BodyMassUnitSelector.hpp"
#include "input/DataGetter.hpp"
#include "input/OptionSelector.hpp"
#include "localization/TextId.hpp"
#include "physics/Constants.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"
#include "ui/ConsoleWriter.hpp"

bool BodyInputBase::isBodyNameAlreadyUsed(const std::string& checkedName) const
{
	return doesAnyBodyMatch([&checkedName](const Body& body) {return body.getName() == checkedName; });
}

bool BodyInputBase::isBodyPositionAlreadyUsed(const Vector3D& position) const
{
	return doesAnyBodyMatch([&position](const Body& body) {return body.getPosition() == position; });
}

double BodyInputBase::promptForBodyMass(const BodyTypeId bodyTypeId) const
{
	ConsoleWriter::writeLine();
	const auto& bodyType{ BodyTypeCatalog::getType(bodyTypeId) };
	const auto massMultiplier{ BodyMassUnitSelector::getInstance().selectMassMultiplier(bodyTypeId) };
	const auto& massInterval{ bodyType.getMassInterval() };
	const auto min{ massInterval.min / massMultiplier };
	const auto max{ massInterval.max / massMultiplier };
	ConsoleWriter::write(TextId::EnterBodyMass, " (", TextId::Interval, ' ', min, " - ", max, "): ");

	return massMultiplier * DataGetter::getValue<double>([min, max](const double x) {return x >= min && x <= max; });
}

std::string BodyInputBase::promptForBodyName() const
{
	ConsoleWriter::write(TextId::EnterOneWordName, ": ");
	auto enteredName{ DataGetter::getSingleWordText() };
	if (isSameAsCurrentName(enteredName)) {
		return enteredName;
	}
	while (isBodyNameAlreadyUsed(enteredName)) {
		ConsoleWriter::write(TextId::BodyNameAlreadyUsedEnterAnother, ": ");
		enteredName = DataGetter::getSingleWordText();
	}
	return enteredName;
}

BodyTypeId BodyInputBase::promptForBodyType() const
{
	const auto bodyTypes{ BodyTypeCatalog::getAvailableTypes() };
	std::vector<OptionSelector::SelectionOption<BodyTypeId>> options{};
	options.reserve(bodyTypes.size());
	for (const auto& bodyType : bodyTypes) {
		options.emplace_back(bodyType.getTextId(), bodyType.getId());
	}
	const auto selectedOption{ OptionSelector::selectOption(options, TextId::SelectBodyType) };
	ConsoleWriter::writeLine(TextId::SelectedBodyType, ": ", selectedOption.textId);
	return selectedOption.value;
}

Vector3D BodyInputBase::promptForBodyPosition() const
{
	ConsoleWriter::writeLine();
	const auto distanceMultiplier{ UnitSelector::selectUnitMultiplier(std::vector<UnitSelector::UnitOption>{
		{TextId::Metre,							1.0},
		{TextId::Kilometre,						physics::KM_MULTIPLIER},
		{TextId::ThousandKilometre,				physics::KKM_MULTIPLIER},
		{TextId::MillionKilometre,				physics::MKM_MULTIPLIER},
		{TextId::AverageEarthToMoonDistance,	physics::EARTH_MOON_DISTANCE},
		{TextId::AstronomicalUnit,				physics::AU}},
		TextId::SelectDistanceUnit) };

	ConsoleWriter::write(TextId::EnterPositionVector, ": ");
	auto enteredPosition{ distanceMultiplier * DataGetter::getVector3D() };
	if (isSameAsCurrentPosition(enteredPosition)) {
		return enteredPosition;
	}
	while (isBodyPositionAlreadyUsed(enteredPosition)) {
		ConsoleWriter::write(TextId::BodyPositionAlreadyOccupiedEnterAnother, ": ");
		enteredPosition = distanceMultiplier * DataGetter::getVector3D();
	}
	return enteredPosition;
}

Vector3D BodyInputBase::promptForBodyVelocity() const
{
	ConsoleWriter::writeLine();
	const auto velocityMultiplier{ UnitSelector::selectUnitMultiplier(std::vector<UnitSelector::UnitOption>{
		{TextId::MetrePerSecond,			1.0},
		{TextId::KilometrePerSecond,		physics::KMS_MULTIPLIER},
		{TextId::ThousandKilometrePerHour,	physics::KKMH_MULTIPLIER},
		{TextId::SpeedOfLight,				physics::C_CONST}},
		TextId::SelectSpeedUnit) };

	ConsoleWriter::write(TextId::EnterVelocityVector, ": ");
	return velocityMultiplier * DataGetter::getVector3D([velocityMultiplier](const double v) {return std::fabs(velocityMultiplier * v) < physics::C_CONST; });
}
