#pragma once
#include <array>
#include <cstddef>
#include <optional>
#include <vector>
#include "OptionSelector.hpp"
#include "simulation/bodies/types/BodyType.hpp"

class BodyMassUnitSelector
{
public:
	static BodyMassUnitSelector& getInstance();
	double selectMassMultiplier(const BodyTypeId bodyTypeId);
private:
	static constexpr std::size_t BODY_TYPE_COUNT{ 7u };
	using UnitVector = std::vector<UnitSelector::UnitOption>;
	using UnitCache = std::array<std::optional<UnitVector>, BODY_TYPE_COUNT>;
	BodyMassUnitSelector() = default;
	BodyMassUnitSelector(const BodyMassUnitSelector&) = delete;
	BodyMassUnitSelector(BodyMassUnitSelector&&) = delete;
	BodyMassUnitSelector& operator=(const BodyMassUnitSelector&) = delete;
	BodyMassUnitSelector& operator=(BodyMassUnitSelector&&) = delete;
	static std::size_t toIndex(const BodyTypeId id) { return static_cast<std::size_t>(id); }
	const UnitVector& getUnitsFor(const BodyTypeId bodyTypeId);
	static UnitVector generateMassUnitVector(const MassInterval& massInterval);
	UnitCache cache{};
};