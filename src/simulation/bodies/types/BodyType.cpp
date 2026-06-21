#include "simulation/bodies/types/BodyType.hpp"
#include <array>
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