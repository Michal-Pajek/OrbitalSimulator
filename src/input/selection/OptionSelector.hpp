#pragma once
#include <optional>
#include <vector>

#include "common/runtime_checks/RuntimeChecks.hpp"
#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"
#include "ui/menu/Menu.hpp"

namespace input::selection
{
    template <typename T>
    struct SelectionOption
    {
        SelectionOption() = delete;
        SelectionOption(localization::TextId optionTextId, T optionValue) : textId{ optionTextId }, value{ optionValue } {}
        localization::TextId textId;
        T value;
    };

    template <typename T>
    SelectionOption<T> selectOption(const std::vector<SelectionOption<T>>& options, const localization::TextId menuTitle)
    {
        const auto size{ options.size() };
        runtime_checks::ensure(size > 0u && size < 10u, runtime_checks::Type::Argument, "Options vector in input::selection::selectOption must be between 1 and 9");

        std::optional<SelectionOption<T>> result{};
        auto key{ '1' };
        std::vector<MenuOption> menuOptions{};
        menuOptions.reserve(size);

        for (const auto& option : options) {
            menuOptions.emplace_back(key++, option.textId, [&result, option]() { result = option; });
        }

        const Menu menu{ menuOptions, menuTitle };
        menu.execute();

        runtime_checks::ensure(result.has_value(), runtime_checks::Type::Logic, "input::selection::selectOption: menu finished without selecting an option");

        return result.value();
    }

    namespace unit
    {
        using UnitOption = SelectionOption<double>;

        inline double selectUnitMultiplier(const std::vector<UnitOption>& options, const localization::TextId menuTitle)
        {
            const auto selectedOption{ selectOption(options, menuTitle) };
            ConsoleWriter::writeLine(localization::TextId::SelectedUnit, ": ", selectedOption.textId);
            return selectedOption.value;
        }
    } // namespace unit
} // namespace input::selection
