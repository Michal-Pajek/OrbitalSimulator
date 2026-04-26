#include "ui/ConsoleWriter.hpp"
#include "localization/Localization.hpp"

void ConsoleWriter::writeError(const std::string_view text)
{
	writeLine("ERROR: ", text);
}

void ConsoleWriter::writeHeadline(const TextId titleId)
{
	write("\t=== ", titleId, " ===\n\n");
}

void ConsoleWriter::writeMenuOption(const TextId textId, const char key, const char separator)
{
	write("\t[ ", key, " ]\t", textId, separator);
}

void ConsoleWriter::writeMenuTitle(const TextId titleId)
{
	writeLine("=== ", titleId, " ===");
}

void ConsoleWriter::writeSingle(const TextId textId)
{
	std::cout << Localization::translate(textId);
}

void ConsoleWriter::writeYesOrNo(const Localization::YesAndNo& yn)
{
	write(" [", yn.yes, " / ", yn.no, "]: ");
}