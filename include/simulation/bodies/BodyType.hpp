#pragma once
#include <array>
#include <vector>
#include "app/Menu.hpp"
#include "localization/TextId.hpp"
#include "physics/Constants.hpp"

enum class BodyType
{
	Meteor,
	Asteroid,
	Comet,
	DwarfPlanet,
	Planet,
	BrownDwarf,
	Star,
	Count
};

namespace BodyTypeImpl
{
	struct MassInterval
	{
		double min;
		double max;
	};

	struct MassUnit
	{
		TextId name;
		double mass;
	};

	inline constexpr std::array<MassUnit, 8u> MassUnitsArray{
		MassUnit{.name{TextId::Kilogram},		.mass{1.0}},
		MassUnit{.name{TextId::Ton},			.mass{physics::TON}},
		MassUnit{.name{TextId::Kiloton},		.mass{physics::KILOTON}},
		MassUnit{.name{TextId::Megaton},		.mass{physics::MEGATON}},
		MassUnit{.name{TextId::MoonMass},		.mass{physics::MOON_MASS}},
		MassUnit{.name{TextId::EarthMass},		.mass{physics::EARTH_MASS}},
		MassUnit{.name{TextId::JupiterMass},	.mass{physics::JUPITER_MASS}},
		MassUnit{.name{TextId::SolarMass},		.mass{physics::SOLAR_MASS}}
	};

	inline constexpr std::array<MassInterval, static_cast<std::size_t>(BodyType::Count)> BodyTypeMassIntervalArray{
		MassInterval{.min{1e-9},	.max{1e8}},
		MassInterval{.min{1e8},		.max{1e21}},
		MassInterval{.min{1e11},	.max{1e18}},
		MassInterval{.min{1e20},	.max{1e24}},
		MassInterval{.min{1e23},	.max{1e28}},
		MassInterval{.min{13.0 * physics::JUPITER_MASS},	.max{80.0 * physics::JUPITER_MASS}},
		MassInterval{.min{0.08 * physics::SOLAR_MASS},		.max{200.0 * physics::SOLAR_MASS}}
	};

	inline constexpr MassInterval getInterval(const BodyType bodyType)
	{
		return BodyTypeMassIntervalArray.at(static_cast<size_t>(bodyType));
	}

	std::vector<MenuOptionPair> getMassUnitVector(const MassInterval massInterval);
}