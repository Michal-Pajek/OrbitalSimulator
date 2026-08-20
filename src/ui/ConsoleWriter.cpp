#include "ui/ConsoleWriter.hpp"

#include "localization/LocalizationManager.hpp"

namespace ConsoleWriter
{
	void writeError(const std::string_view text)
	{
		writeLine("ERROR: ", text);
	}

	void writeHeadline(const TextId titleId)
	{
		write("\t=== ", titleId, " ===\n\n");
	}

	void writeMenuOption(const TextId textId, const char key, const char separator)
	{
		write("\t[ ", key, " ]\t", textId, separator);
	}

	void writeMenuTitle(const TextId titleId)
	{
		writeLine("=== ", titleId, " ===");
	}

	void writeSingle(const TextId textId)
	{
		std::cout << LocalizationManager::getInstance().get(textId);
	}

	void writeYesOrNo(const LocalizationManager::YesAndNo& yn)
	{
		write(" [", yn.yes, " / ", yn.no, "]: ");
	}
} // namespace ConsoleWriter
