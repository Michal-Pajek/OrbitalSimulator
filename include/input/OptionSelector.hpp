#pragma once
#include <optional>
#include <vector>
#include "app/ExceptionHandler.hpp"
#include "app/Menu.hpp"
#include "localization/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace OptionSelector
{
    template <typename T>
    struct SelectionOption
    {
        SelectionOption() = delete;
        SelectionOption(TextId optionTextId, T optionValue) : textId{ optionTextId }, value{ optionValue } {}
        TextId textId;
        T value;
    };

    template <typename T>
    SelectionOption<T> selectOption(const std::vector<SelectionOption<T>>& options, const TextId menuTitle)
    {
        const auto size{ options.size() };
        ExceptionHandler::ensure(size > 0u && size < 10u, ExceptionHandler::ExceptionType::Argument, "Options vector in OptionSelector::selectOption must be between 1 and 9");

        std::optional<SelectionOption<T>> result{};
        auto key{ '1' };
        std::vector<MenuOption> menuOptions{};
        menuOptions.reserve(size);

        for (const auto& option : options) {
            menuOptions.emplace_back(key++, option.textId, [&result, option]() { result = option; });
        }

        const Menu menu{ menuOptions, menuTitle };
        menu.execute();

        ExceptionHandler::ensure(result.has_value(), ExceptionHandler::ExceptionType::Logic, "OptionSelector::selectOption: menu finished without selecting an option");

        return result.value();
    }
}

namespace UnitSelector
{
    using UnitOption = OptionSelector::SelectionOption<double>;

    inline double selectUnitMultiplier(const std::vector<UnitOption>& options, const TextId menuTitle)
    {
        const auto selectedOption{ OptionSelector::selectOption(options, menuTitle) };
        ConsoleWriter::writeLine(TextId::SelectedUnit, ": ", selectedOption.textId);
        return selectedOption.value;
    }
}
