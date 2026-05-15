#include "simulation/bodies/BodyType.hpp"
#include <vector>
#include "app/Menu.hpp"
#include "localization/TextId.hpp"

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
		result.emplace_back(TextId::Kilogram, 1.0);
	}
	return result;
}
