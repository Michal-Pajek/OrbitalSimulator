#pragma once
#include <iostream>
#include <string_view>
#include <utility>
#include "localization/Localization.hpp"
#include "localization/TextId.hpp"

namespace ConsoleWriter
{
	void writeError(const std::string_view text);
	void writeHeadline(const TextId titleId);
	void writeMenuOption(const TextId textId, const char key, const char separator);
	void writeMenuTitle(const TextId titleId);
	void writeSingle(TextId id);
	void writeYesOrNo(const Localization::YesAndNo& yn);

	template <typename T>
	void writeSingle(const T& value)
	{
		std::cout << value;
	}

	template <typename... Args>
	void write(Args&&... args)
	{
		(writeSingle(std::forward<Args>(args)), ...);
	}

	template <typename... Args>
	void writeLine(Args&&... args)
	{
		(writeSingle(std::forward<Args>(args)), ...);
		std::cout << '\n';
	}
}