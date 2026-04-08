#include "ui/ConsoleWriter.hpp"
#include <iostream>
#include "localization/Localization.hpp"

void ConsoleWriter::write(const TextId textId)
{
	std::cout << Localization::translate(textId);
}

void ConsoleWriter::writeError(const std::string_view& text)
{
	std::cout << text << '\n';
}

void ConsoleWriter::writeHeadline(const TextId titleId)
{
	std::cout << "\t=== " << Localization::translate(titleId) << " ===\n\n";
}

void ConsoleWriter::writeMenuOption(const TextId textId, const char key, const char separator)
{
	std::cout << "\t[ " << key << " ]\t" << Localization::translate(textId) << separator;
}

void ConsoleWriter::writeMenuTitle(const TextId titleId)
{
	std::cout << "=== " << Localization::translate(titleId) << " ===\n";
}

void ConsoleWriter::writeNewLine()
{
	std::cout << '\n';
}

void ConsoleWriter::writeYesOrNo(const Localization::YesAndNo& yn)
{
	std::cout << " [" << yn.yes << " / " << yn.no << "]: ";
}