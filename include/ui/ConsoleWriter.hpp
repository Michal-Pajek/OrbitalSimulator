#pragma once
#include <string_view>
#include "localization/Localization.hpp"
#include "localization/TextId.hpp"

namespace ConsoleWriter
{
	void write(const TextId textId);
	void writeError(const std::string_view& text);
	void writeHeadline(const TextId titleId);
	void writeMenuOption(const TextId textId, const char key, const char separator);
	void writeMenuTitle(const TextId titleId);
	void writeNewLine();
	void writeYesOrNo(const Localization::YesAndNo& yn);
}