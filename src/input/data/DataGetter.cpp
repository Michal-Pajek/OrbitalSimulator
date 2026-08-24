#include "input/data/DataGetter.hpp"

#include <limits>

#include "filesystem/FileNameValidation.hpp"

namespace DataGetter
{
	bool detail::recoverFromInputFailure()
	{
		if (std::cin.fail()) {
			std::cin.clear();
			discardLineRemainder();
			return false;
		}
		return true;
	}

	void detail::discardLineRemainder()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::size_t getSelectionNumber(const TextId textId, const std::size_t count, bool includeZero)
	{
		ConsoleWriter::write(textId, ": ");
		return static_cast<std::size_t>(getValue<int>([countInt = static_cast<int>(count), includeZero](const int value) {
			return value >= (includeZero ? 0 : 1) && value <= countInt;
			}));
	}

	std::string getSingleWordText()
	{
		return detail::getValidatedInput<std::string>([](const std::string& text) {
			return !text.empty();
			});
	}

	std::string getFileBaseName()
	{
		return detail::getValidatedInput<std::string>([](const std::string& text) {
			return FileNameValidation::isValidBaseName(text);
			});
	}
} // namespace DataGetter
