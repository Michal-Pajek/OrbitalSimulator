#pragma once
#include <optional>
#include <stdexcept>
#include <vector>
#include "app/Menu.hpp"
#include "localization/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace OptionSelector
{
    template <typename T>
    struct SelectionOption
    {
        SelectionOption() = delete;
        SelectionOption(TextId _textId, T _value) : textId{ _textId }, value{ _value } {}
        TextId textId;
        T value;
    };

    template <typename T>
    SelectionOption<T> selectOption(const std::vector<SelectionOption<T>>& options, const TextId menuTitle)
    {
        const auto size{ options.size() };
        if (size == 0 || size >= 10u) {
            throw std::invalid_argument{"Options vector in OptionSelector::selectOption must be between 1 and 9"};
        }

        std::optional<SelectionOption<T>> result{};
        auto key{ '1' };
        std::vector<MenuOption> menuOptions{};
        menuOptions.reserve(size);

        for (const auto& option : options) {
            menuOptions.emplace_back(key++, option.textId, [&result, option]() { result = option; });
        }

        const Menu menu{ menuOptions, menuTitle };
        menu.execute();

        if (!result) {
            throw std::logic_error{ "OptionSelector::selectOption: menu finished without selecting an option" };
        }

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
