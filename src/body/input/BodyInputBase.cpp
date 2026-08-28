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

	bool BodyInputBase::isBodyPositionAlreadyUsed(const math::Vector3D& position) const
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
		ConsoleWriter::write(localization::TextId::EnterBodyMass, " (", localization::TextId::Interval, ' ', min, " - ", max, "): ");

		return massMultiplier * ::input::data::getValue<double>([min, max](const double x) {return x >= min && x <= max; });
	}

	std::string BodyInputBase::promptForBodyName() const
	{
		ConsoleWriter::write(localization::TextId::EnterOneWordName, ": ");
		auto enteredName{ ::input::data::getSingleWordText() };
		if (isSameAsCurrentName(enteredName)) {
			return enteredName;
		}
		while (isBodyNameAlreadyUsed(enteredName)) {
			ConsoleWriter::write(localization::TextId::BodyNameAlreadyUsedEnterAnother, ": ");
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
		const auto selectedOption{ ::input::selection::selectOption(options, localization::TextId::SelectBodyType) };
		ConsoleWriter::writeLine(localization::TextId::SelectedBodyType, ": ", selectedOption.textId);
		return selectedOption.value;
	}

	math::Vector3D BodyInputBase::promptForBodyPosition() const
	{
		ConsoleWriter::writeLine();
		const auto distanceMultiplier{ ::input::selection::unit::selectUnitMultiplier(std::vector<::input::selection::unit::UnitOption>{
			{localization::TextId::Metre,						1.0},
			{localization::TextId::Kilometre,					physics::KM_MULTIPLIER},
			{localization::TextId::ThousandKilometre,			physics::KKM_MULTIPLIER},
			{localization::TextId::MillionKilometre,			physics::MKM_MULTIPLIER},
			{localization::TextId::AverageEarthToMoonDistance,	physics::EARTH_MOON_DISTANCE},
			{localization::TextId::AstronomicalUnit,			physics::AU}},
			localization::TextId::SelectDistanceUnit) };

		ConsoleWriter::write(localization::TextId::EnterPositionVector, ": ");
		auto enteredPosition{ distanceMultiplier * ::input::data::getVector3D() };
		if (isSameAsCurrentPosition(enteredPosition)) {
			return enteredPosition;
		}
		while (isBodyPositionAlreadyUsed(enteredPosition)) {
			ConsoleWriter::write(localization::TextId::BodyPositionAlreadyOccupiedEnterAnother, ": ");
			enteredPosition = distanceMultiplier * ::input::data::getVector3D();
		}
		return enteredPosition;
	}

	math::Vector3D BodyInputBase::promptForBodyVelocity() const
	{
		ConsoleWriter::writeLine();
		const auto velocityMultiplier{ ::input::selection::unit::selectUnitMultiplier(std::vector<::input::selection::unit::UnitOption>{
			{localization::TextId::MetrePerSecond,				1.0},
			{localization::TextId::KilometrePerSecond,			physics::KMS_MULTIPLIER},
			{localization::TextId::ThousandKilometrePerHour,	physics::KKMH_MULTIPLIER},
			{localization::TextId::SpeedOfLight,				physics::C_CONST}},
			localization::TextId::SelectSpeedUnit) };

		ConsoleWriter::write(localization::TextId::EnterVelocityVector, ": ");
		return velocityMultiplier * ::input::data::getVector3D([velocityMultiplier](const double x, const double y, const double z) {
			return physics::isSubLightVelocity(
				x * velocityMultiplier,
				y * velocityMultiplier,
				z * velocityMultiplier);
			});
	}
} // namespace body::input
