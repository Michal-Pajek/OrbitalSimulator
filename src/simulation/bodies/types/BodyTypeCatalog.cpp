#include "simulation/bodies/types/BodyTypeCatalog.hpp"
#include <stdexcept>
#include "localization/TextId.hpp"
#include "physics/Constants.hpp"

#define GET_TEXT_AND_BODY_TYPE_IDS(name) TextId::name, BodyTypeId::name

const std::array<BodyType, BODY_TYPE_COUNT> BodyTypeCatalog::bodyTypesArray{
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(Meteor),		MassInterval{.min{1e-9},	.max{1e8}}},
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(Asteroid),		MassInterval{.min{1e8},		.max{1e21}}},
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(Comet),			MassInterval{.min{1e11},	.max{1e18}}},
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(Moon),			MassInterval{.min{1e12},	.max{1e26}}},
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(DwarfPlanet),	MassInterval{.min{1e20},	.max{1e24}}},
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(Planet),		MassInterval{.min{1e23},	.max{1e28}}},
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(BrownDwarf),	MassInterval{.min{13.0 * physics::JUPITER_MASS},	.max{80.0 * physics::JUPITER_MASS}}},
		BodyType{GET_TEXT_AND_BODY_TYPE_IDS(Star),			MassInterval{.min{0.08 * physics::SOLAR_MASS},		.max{200.0 * physics::SOLAR_MASS}}}
	};

#undef GET_TEXT_AND_BODY_TYPE_IDS

const BodyType& BodyTypeCatalog::getType(const BodyTypeId id)
{
	const auto idx{ static_cast<std::size_t>(id) };
	if (idx >= BODY_TYPE_COUNT) {
		throw std::logic_error{ "BodyTypeCatalog::getType: unknown BodyTypeId" };
	}
	return bodyTypesArray.at(idx);
}
