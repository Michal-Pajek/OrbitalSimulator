#pragma once
#include <span>
#include <string_view>

#include "body/Body.hpp"

namespace scenario
{
	struct Scenario;

	namespace summary
	{
		void print(std::string_view name, std::span<const body::Body> bodies);
		void print(const Scenario& scenario);
	} // namespace summary
} // namespace scenario
