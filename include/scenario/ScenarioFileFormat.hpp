#pragma once
#include <string_view>

namespace ScenarioFileFormat
{
	inline constexpr std::string_view extension{ ".sav" };
	inline constexpr std::string_view identifier{ "ORBITAL_SCENARIO" };
	inline constexpr auto currentVersion{ 1 };
}
