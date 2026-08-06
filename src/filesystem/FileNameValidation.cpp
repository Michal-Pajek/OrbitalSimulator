#include "filesystem/FileNameValidation.hpp"
#include <algorithm>

namespace FileNameValidation
{
	bool isValidBaseName(const std::string_view name)
	{
		if (name.empty() ||
			name == "." ||
			name == "..") {
			return false;
		}

		return std::ranges::none_of(name, [](const char ch) {
			constexpr std::string_view forbiddenChars{ "/\\<>:\"?*|" };
			const auto unsignedChar{ static_cast<unsigned char>(ch) };
			return unsignedChar < 32 || forbiddenChars.find(ch) != std::string_view::npos;
			});
	}
}
