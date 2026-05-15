#include "simulation/bodies/BodyType.hpp"
#include <stdexcept>
#include <vector>
#include "localization/TextId.hpp"
#include "physics/Constants.hpp"

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
}

const BodyType* BodyType::getType(const TextId textId)
{
	for (const auto& x : bodyTypeList) {
		if (x.m_textId == textId) {
			return &x;
		}
	}
	throw std::runtime_error("No textId match in BodyType");
}

std::vector<UnitSelector::UnitOption> BodyType::generateMassUnitVector()
{
	constexpr double TOLERANCE{ 1e3 };
	std::vector<UnitSelector::UnitOption> result{};
	for (const auto& x : massUnitsArray) {
		const auto& mass{ x.mass };
		if (mass >= m_massInterval.min / TOLERANCE && mass <= m_massInterval.max * TOLERANCE) {
			result.emplace_back(x.name, mass);
		}
	}
	if (result.empty()) {
		result.emplace_back(TextId::Kilogram, 1.0);
	}
	return result;
}

const std::array<BodyType, 7> BodyType::bodyTypeList{
		BodyType{TextId::Meteor,		MassInterval{.min{1e-9},	.max{1e8}}},
		BodyType{TextId::Asteroid,		MassInterval{.min{1e8},		.max{1e21}}},
		BodyType{TextId::Comet,			MassInterval{.min{1e11},	.max{1e18}}},
		BodyType{TextId::DwarfPlanet,	MassInterval{.min{1e20},	.max{1e24}}},
		BodyType{TextId::Planet,		MassInterval{.min{1e23},	.max{1e28}}},
		BodyType{TextId::BrownDwarf,	MassInterval{.min{13.0 * physics::JUPITER_MASS},	.max{80.0 * physics::JUPITER_MASS}}},
		BodyType{TextId::Star,			MassInterval{.min{0.08 * physics::SOLAR_MASS},		.max{200.0 * physics::SOLAR_MASS}}}
};