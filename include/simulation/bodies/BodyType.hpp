#pragma once
#include <array>
#include "physics/Constants.hpp"

struct MassInterval
{
	double min;
	double max;
	double defaultUnit{ 1.0 };
};

enum class BodyType
{
	Custom,
	Meteor,
	Asteroid,
	Comet,
	DwarfPlanet,
	Planet,
	BrownDwarf,
	Star,
	Count
};

inline constexpr std::array<MassInterval, static_cast<std::size_t>(BodyType::Count)> BodyTypeMassIntervalMap{
	MassInterval{.min{1e-9},	.max{1e8}},
	MassInterval{.min{1e8},		.max{1e21}},
	MassInterval{.min{1e11},	.max{1e18}},
	MassInterval{.min{1e20},	.max{1e24}},
	MassInterval{.min{1e23},	.max{1e28}},
	MassInterval{.min{13.0},	.max{80.0},		.defaultUnit = physics::JUPITER_MASS },
	MassInterval{.min{0.08},	.max{200.0},	.defaultUnit = physics::SOLAR_MASS }
};

inline constexpr MassInterval getInterval(const BodyType bodyType)
{
	return BodyTypeMassIntervalMap.at(static_cast<size_t>(bodyType));
}

inline MassInterval getStandarizedInterval(const BodyType bodyType)
{
	const auto interval{ getInterval(bodyType) };
	return MassInterval{ .min{interval.min * interval.defaultUnit}, .max{interval.max * interval.defaultUnit} };
}