#include "TestBodyCreator.hpp"
#include <cstddef>
#include <numeric>
#include <stdexcept>
#include "simulation/bodies/types/BodyType.hpp"
#include "simulation/bodies/types/BodyTypeCatalog.hpp"

namespace
{
	BodyTypeId getMatchingBodyTypeId(const double mass)
	{
		for (std::size_t id{}; id < BODY_TYPE_COUNT; ++id) {
			if (BodyTypeCatalog::isMassInRange(static_cast<BodyTypeId>(id), mass)) {
				return static_cast<BodyTypeId>(id);
			}
		}
		throw std::invalid_argument{ "There is no matching type for the specified mass" };
	}
}

namespace TestBodyCreator
{
	double getProperMass(const BodyTypeId id)
	{
		const auto [min, max] {BodyTypeCatalog::getType(id).getMassInterval()};
		return std::midpoint(min, max);
	}

	Body createTestBody(const double mass, const Vector3D& position, const Vector3D& velocity, const std::string& name)
	{
		const auto typeId{ getMatchingBodyTypeId(mass) };
		return Body{ name, typeId, mass, position, velocity };
	}
} // TestBodyCreator
