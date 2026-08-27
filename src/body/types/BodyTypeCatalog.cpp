#include "body/types/BodyTypeCatalog.hpp"

#include <cstddef>

#include "common/runtime_checks/RuntimeChecks.hpp"
#include "localization/core/TextId.hpp"
#include "physics/Constants.hpp"

namespace body
{
#define BODY_TYPE_ARGS(name) TextId::name, #name, BodyTypeId::name

	const std::array<BodyType, BODY_TYPE_COUNT> BodyTypeCatalog::bodyTypesArray{
			BodyType{BODY_TYPE_ARGS(Meteor),		MassInterval{.min{1e-9},	.max{1e8}}},
			BodyType{BODY_TYPE_ARGS(Asteroid),		MassInterval{.min{1e8},		.max{1e21}}},
			BodyType{BODY_TYPE_ARGS(Comet),			MassInterval{.min{1e11},	.max{1e18}}},
			BodyType{BODY_TYPE_ARGS(Moon),			MassInterval{.min{1e12},	.max{1e24}}},
			BodyType{BODY_TYPE_ARGS(DwarfPlanet),	MassInterval{.min{1e20},	.max{1e24}}},
			BodyType{BODY_TYPE_ARGS(Planet),		MassInterval{.min{1e23},	.max{1e28}}},
			BodyType{BODY_TYPE_ARGS(BrownDwarf),	MassInterval{.min{13.0 * physics::JUPITER_MASS},	.max{80.0 * physics::JUPITER_MASS}}},
			BodyType{BODY_TYPE_ARGS(Star),			MassInterval{.min{0.08 * physics::SOLAR_MASS},		.max{200.0 * physics::SOLAR_MASS}}}
	};

#undef BODY_TYPE_ARGS

	const BodyType& BodyTypeCatalog::getType(const BodyTypeId id)
	{
		const auto idx{ static_cast<std::size_t>(id) };
		runtime_checks::ensure(idx < BODY_TYPE_COUNT, runtime_checks::Type::Logic, "BodyTypeCatalog::getType: unknown BodyTypeId");
		return bodyTypesArray.at(idx);
	}

	bool BodyTypeCatalog::isMassInRange(const BodyTypeId id, const double mass)
	{
		const auto [min, max] {getType(id).getMassInterval()};
		return min <= mass && mass <= max;
	}

	std::optional<BodyTypeId> BodyTypeCatalog::deserializeKey(std::string_view serializationKey)
	{
		for (const auto& bodyType : bodyTypesArray) {
			if (bodyType.getSerializationKey() == serializationKey) {
				return bodyType.getId();
			}
		}
		return {};
	}
} // namespace body
