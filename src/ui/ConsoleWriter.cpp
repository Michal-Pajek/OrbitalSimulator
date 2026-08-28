#include "ui/ConsoleWriter.hpp"

#include "localization/LocalizationManager.hpp"

namespace ConsoleWriter
{
	void writeError(const std::string_view text)
	{
		writeLine("ERROR: ", text);
	}

	void writeHeadline(const localization::TextId titleId)
	{
		write("\t=== ", titleId, " ===\n\n");
	}

	void writeMenuOption(const localization::TextId textId, const char key, const char separator)
	{
		write("\t[ ", key, " ]\t", textId, separator);
	}

	void writeMenuTitle(const localization::TextId titleId)
	{
		writeLine("=== ", titleId, " ===");
	}

	void writeSingle(const localization::TextId textId)
	{
		std::cout << localization::LocalizationManager::getInstance().get(textId);
	}

	void writeYesOrNo(const localization::LocalizationManager::YesAndNo& yn)
	{
		write(" [", yn.yes, " / ", yn.no, "]: ");
	}
} // namespace ConsoleWriter
