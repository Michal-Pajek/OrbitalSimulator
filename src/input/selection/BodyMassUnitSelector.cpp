#include "input/selection/BodyMassUnitSelector.hpp"

#include "localization/core/TextId.hpp"
#include "physics/Constants.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"

namespace
{
	struct MassUnit
	{
		TextId name;
		double mass;
	};

	constexpr std::array massUnitsArray{
		MassUnit{.name{TextId::Kilogram},		.mass{1.0}},
		MassUnit{.name{TextId::Ton},			.mass{physics::TON}},
		MassUnit{.name{TextId::Kiloton},		.mass{physics::KILOTON}},
		MassUnit{.name{TextId::Megaton},		.mass{physics::MEGATON}},
		MassUnit{.name{TextId::MoonMass},		.mass{physics::MOON_MASS}},
		MassUnit{.name{TextId::EarthMass},		.mass{physics::EARTH_MASS}},
		MassUnit{.name{TextId::JupiterMass},	.mass{physics::JUPITER_MASS}},
		MassUnit{.name{TextId::SolarMass},		.mass{physics::SOLAR_MASS}}
	};
} // anonymous namespace

BodyMassUnitSelector& BodyMassUnitSelector::getInstance() {
	static BodyMassUnitSelector instance{};
	return instance;
}

double BodyMassUnitSelector::selectMassMultiplier(const BodyTypeId bodyTypeId) {
	return UnitSelector::selectUnitMultiplier(getUnitsFor(bodyTypeId), TextId::SelectMassUnit);
}

auto BodyMassUnitSelector::getUnitsFor(const BodyTypeId bodyTypeId) -> const UnitVector& {
	const auto idx{ toIndex(bodyTypeId) };
	if (!cache.at(idx)) {
		const auto& bodyType{ BodyTypeCatalog::getType(bodyTypeId) };
		cache.at(idx).emplace(generateMassUnitVector(bodyType.getMassInterval()));
	}
	return cache.at(idx).value();
}

auto BodyMassUnitSelector::generateMassUnitVector(const MassInterval& massInterval) -> UnitVector {
	// The unit list is selected automatically based on the body type mass interval.
	// This avoids hardcoding unit sets per BodyTypeId. The tolerance may be tuned later.
	constexpr double TOLERANCE{ 1e3 };
	UnitVector result{};
	for (const auto& x : massUnitsArray) {
		const auto& mass{ x.mass };
		if (mass >= massInterval.min / TOLERANCE && mass <= massInterval.max * TOLERANCE) {
			result.emplace_back(x.name, mass);
		}
	}
	if (result.empty()) {
		result.emplace_back(TextId::Kilogram, 1.0);
	}
	return result;
}
