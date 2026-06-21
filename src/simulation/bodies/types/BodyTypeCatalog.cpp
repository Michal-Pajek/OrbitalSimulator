#include "simulation/bodies/types/BodyTypeCatalog.hpp"
#include <stdexcept>
#include "localization/TextId.hpp"
#include "physics/Constants.hpp"

const std::array<BodyType, 7u> BodyTypeCatalog::bodyTypesArray{
		BodyType{TextId::Meteor,			BodyTypeId::Meteor,			MassInterval{.min{1e-9},	.max{1e8}}},
		BodyType{TextId::Asteroid,			BodyTypeId::Asteroid,		MassInterval{.min{1e8},		.max{1e21}}},
		BodyType{TextId::Comet,				BodyTypeId::Comet,			MassInterval{.min{1e11},	.max{1e18}}},
		BodyType{TextId::DwarfPlanetOrMoon,	BodyTypeId::DwarfPlanet,	MassInterval{.min{1e20},	.max{1e24}}},
		BodyType{TextId::Planet,			BodyTypeId::Planet,			MassInterval{.min{1e23},	.max{1e28}}},
		BodyType{TextId::BrownDwarf,		BodyTypeId::BrownDwarf,		MassInterval{.min{13.0 * physics::JUPITER_MASS},	.max{80.0 * physics::JUPITER_MASS}}},
		BodyType{TextId::Star,				BodyTypeId::Star,			MassInterval{.min{0.08 * physics::SOLAR_MASS},		.max{200.0 * physics::SOLAR_MASS}}}
	};

const BodyType& BodyTypeCatalog::getType(const BodyTypeId id) // todo: change to binary search
{
	for (const auto& type : bodyTypesArray) {
		if (id == type.m_id) {
			return type;
		}
	}
	throw std::logic_error{ "BodyTypeCatalog::getType: unknown BodyTypeId" };
}
