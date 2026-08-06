#include "input/DataGetter.hpp"
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
