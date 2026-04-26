#include "input/DataGetter.hpp"
#include <limits>

bool DataGetter::detail::recoverFromInputFailure()
{
	if (std::cin.fail()) {
		std::cin.clear();
		discardLineRemainder();
		return false;
	}
	return true;
}

void DataGetter::detail::discardLineRemainder()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string DataGetter::getSingleWordText()
{
	return detail::getValidatedInput<std::string>([](const std::string& text) { return !text.empty(); });
}