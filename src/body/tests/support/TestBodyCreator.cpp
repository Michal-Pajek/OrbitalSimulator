#include "body/tests/support/TestBodyCreator.hpp"

#include <cstddef>
#include <numeric>
#include <stdexcept>

#include "body/types/BodyType.hpp"
#include "body/types/BodyTypeCatalog.hpp"

namespace body::tests
{
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
	} // anonymous namespace

	double getProperMass(const BodyTypeId id)
	{
		const auto [min, max] {BodyTypeCatalog::getType(id).getMassInterval()};
		return std::midpoint(min, max);
	}

	Body createTestBody(const double mass, const math::Vector3D& position, const math::Vector3D& velocity, const std::string& name)
	{
		const auto typeId{ getMatchingBodyTypeId(mass) };
		return Body{ name, typeId, mass, position, velocity };
	}
} // namespace body::tests
