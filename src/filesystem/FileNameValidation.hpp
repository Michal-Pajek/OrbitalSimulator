#pragma once
#include <string_view>

namespace filesystem::validation
{
	bool isValidBaseName(std::string_view name);
} // namespace filesystem::validation
