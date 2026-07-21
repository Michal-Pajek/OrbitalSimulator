#include "input/DataGetter.hpp"
#include <algorithm>
#include <limits>
#include <string_view>

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
		return detail::getValidatedInput<std::string>([](const std::string& text) { return !text.empty(); });
	}

	std::string getFileBaseName()
	{
		const auto predicate{ [](const std::string& text) {
			if (text.empty()) {
				return false;
			}
			constexpr std::string_view forbiddenChars{ "/\\<>:\"?*|" };
			return std::ranges::none_of(text, [forbiddenChars](char ch) {return forbiddenChars.find(ch) != std::string_view::npos; });
		} };
		return detail::getValidatedInput<std::string>(predicate);
	}
} // namespace DataGetter
