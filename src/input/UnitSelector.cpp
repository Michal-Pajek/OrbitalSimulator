#include "input/UnitSelector.hpp"
#include <stdexcept>
#include "app/Menu.hpp"
#include "ui/ConsoleWriter.hpp"

namespace UnitSelector
{
	double selectUnitMultiplier(const std::vector<UnitOption>& options, const TextId menuTitle)
	{
		const auto size{ options.size() };
		if (size == 0 || size >= 10u) {
			throw std::invalid_argument("Options vector in selectUnitMultiplier must be between 1 and 9");
		}

		double result{};
		TextId selectedUnit;
		auto key{ '1' };
		std::vector<MenuOption> menuOptions{};
		menuOptions.reserve(size);
		for (size_t idx{}; idx < size; ++idx) {
			const auto& multiplier{ options.at(idx).multiplier };
			const auto& textId{ options.at(idx).textId };
			menuOptions.emplace_back(key++, textId, [&result, &selectedUnit, multiplier, textId]() {result = multiplier; selectedUnit = textId; });
		}

		const Menu selectUnitMenu{ menuOptions, menuTitle };
		selectUnitMenu.execute();
		ConsoleWriter::writeLine(TextId::SelectedUnit, ": ", selectedUnit);
		return result;
	}
}