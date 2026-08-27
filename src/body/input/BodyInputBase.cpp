#include "body/input/BodyInputBase.hpp"

#include "body/input/BodyMassUnitSelector.hpp"

#include "body/types/BodyTypeCatalog.hpp"

#include "input/data/DataGetter.hpp"
#include "input/selection/OptionSelector.hpp"
#include "localization/core/TextId.hpp"
#include "physics/Constants.hpp"
#include "physics/Validation.hpp"
#include "ui/ConsoleWriter.hpp"

namespace body::input
{
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

		return massMultiplier * ::input::data::getValue<double>([min, max](const double x) {return x >= min && x <= max; });
	}

	std::string BodyInputBase::promptForBodyName() const
	{
		ConsoleWriter::write(TextId::EnterOneWordName, ": ");
		auto enteredName{ ::input::data::getSingleWordText() };
		if (isSameAsCurrentName(enteredName)) {
			return enteredName;
		}
		while (isBodyNameAlreadyUsed(enteredName)) {
			ConsoleWriter::write(TextId::BodyNameAlreadyUsedEnterAnother, ": ");
			enteredName = ::input::data::getSingleWordText();
		}
		return enteredName;
	}

	BodyTypeId BodyInputBase::promptForBodyType() const
	{
		const auto bodyTypes{ BodyTypeCatalog::getAvailableTypes() };
		std::vector<::input::selection::SelectionOption<BodyTypeId>> options{};
		options.reserve(bodyTypes.size());
		for (const auto& bodyType : bodyTypes) {
			options.emplace_back(bodyType.getTextId(), bodyType.getId());
		}
		const auto selectedOption{ ::input::selection::selectOption(options, TextId::SelectBodyType) };
		ConsoleWriter::writeLine(TextId::SelectedBodyType, ": ", selectedOption.textId);
		return selectedOption.value;
	}

	Vector3D BodyInputBase::promptForBodyPosition() const
	{
		ConsoleWriter::writeLine();
		const auto distanceMultiplier{ ::input::selection::unit::selectUnitMultiplier(std::vector<::input::selection::unit::UnitOption>{
			{TextId::Metre,							1.0},
			{TextId::Kilometre,						physics::KM_MULTIPLIER},
			{TextId::ThousandKilometre,				physics::KKM_MULTIPLIER},
			{TextId::MillionKilometre,				physics::MKM_MULTIPLIER},
			{TextId::AverageEarthToMoonDistance,	physics::EARTH_MOON_DISTANCE},
			{TextId::AstronomicalUnit,				physics::AU}},
			TextId::SelectDistanceUnit) };

		ConsoleWriter::write(TextId::EnterPositionVector, ": ");
		auto enteredPosition{ distanceMultiplier * ::input::data::getVector3D() };
		if (isSameAsCurrentPosition(enteredPosition)) {
			return enteredPosition;
		}
		while (isBodyPositionAlreadyUsed(enteredPosition)) {
			ConsoleWriter::write(TextId::BodyPositionAlreadyOccupiedEnterAnother, ": ");
			enteredPosition = distanceMultiplier * ::input::data::getVector3D();
		}
		return enteredPosition;
	}

	Vector3D BodyInputBase::promptForBodyVelocity() const
	{
		ConsoleWriter::writeLine();
		const auto velocityMultiplier{ ::input::selection::unit::selectUnitMultiplier(std::vector<::input::selection::unit::UnitOption>{
			{TextId::MetrePerSecond,			1.0},
			{TextId::KilometrePerSecond,		physics::KMS_MULTIPLIER},
			{TextId::ThousandKilometrePerHour,	physics::KKMH_MULTIPLIER},
			{TextId::SpeedOfLight,				physics::C_CONST}},
			TextId::SelectSpeedUnit) };

		ConsoleWriter::write(TextId::EnterVelocityVector, ": ");
		return velocityMultiplier * ::input::data::getVector3D([velocityMultiplier](const double x, const double y, const double z) {
			return physics::isSubLightVelocity(
				x * velocityMultiplier,
				y * velocityMultiplier,
				z * velocityMultiplier);
			});
	}
} // namespace body::input
