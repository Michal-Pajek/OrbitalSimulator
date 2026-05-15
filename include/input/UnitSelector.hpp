#pragma once
#include <vector>
#include "localization/TextId.hpp"

namespace UnitSelector
{
	struct UnitOption {
		TextId textId;
		double multiplier;
		UnitOption() = delete;
		UnitOption(TextId _textId, double _multiplier) : textId{ _textId }, multiplier{ _multiplier } {}
	};

	double selectUnitMultiplier(const std::vector<UnitOption>& options, const TextId menuTitle);
}