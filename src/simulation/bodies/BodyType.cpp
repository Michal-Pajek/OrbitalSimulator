#include "simulation/bodies/BodyType.hpp"

std::vector<MenuOptionPair> BodyTypeImpl::getMassUnitVector(const MassInterval massInterval)
{
	constexpr double TOLERANCE{ 1e3 };
	std::vector<MenuOptionPair> result{};
	for (const auto& x : MassUnitsArray) {
		const auto& mass{ x.mass };
		if (mass >= massInterval.min / TOLERANCE && mass <= massInterval.max * TOLERANCE) {
			result.emplace_back(x.name, mass);
		}
	}
	if (result.empty()) {
		// TODO: throw exception
	}
	return result;
}
