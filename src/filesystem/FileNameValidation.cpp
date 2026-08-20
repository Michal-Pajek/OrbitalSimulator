#include "filesystem/FileNameValidation.hpp"

#include <algorithm>
#include <cctype>

namespace FileNameValidation
{
	namespace
	{
		bool equalsIgnoreCase(std::string_view a, std::string_view b)
		{
			return std::ranges::equal(a, b, [](char x, char y) {
				return std::tolower(static_cast<unsigned char>(x)) == std::tolower(static_cast<unsigned char>(y));
				});
		}

		bool isReservedName(std::string_view name)
		{
			const auto dotPosition{ name.find('.') };
			const auto base{ name.substr(0, dotPosition) };

			constexpr std::string_view reservedNames[]{ "AUX", "CON", "PRN", "NUL" };

			for (const auto reservedName : reservedNames) {
				if (equalsIgnoreCase(base, reservedName)) {
					return true;
				}
			}

			constexpr std::string_view reservedPrefixes[]{ "COM", "LPT" };
			for (const auto prefix : reservedPrefixes) {
				for (char digit{ '1' }; digit <= '9'; ++digit) {
					if (base.size() == 4 &&
						equalsIgnoreCase(base.substr(0, 3), prefix) &&
						base[3] == digit) {
						return true;
					}
				}
			}

			return false;
		}

		bool hasInvalidTrailingCharacter(const std::string_view name)
		{
			return name.back() == ' ' || name.back() == '.';
		}
	} // anonymous namespace

	bool isValidBaseName(const std::string_view name)
	{
		if (name.empty() ||
			name == "." ||
			name == "..") {
			return false;
		}

		if (isReservedName(name)) {
			return false;
		}

		if (hasInvalidTrailingCharacter(name)) {
			return false;
		}

		return std::ranges::none_of(name, [](const char ch) {
			constexpr std::string_view forbiddenChars{ "/\\<>:\"?*|" };
			const auto unsignedChar{ static_cast<unsigned char>(ch) };
			return unsignedChar < 32 || forbiddenChars.find(ch) != std::string_view::npos;
			});
	}
} // namespace FileNameValidation
