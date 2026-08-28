#pragma once
#include <optional>

#include "scenario/core/Scenario.hpp"

namespace scenario::loader
{
	enum class LoadStatus
	{
		Loaded,
		Canceled,
		NoSavedScenarios,
		Failed
	};

	struct LoadResult
	{
		LoadStatus status{ LoadStatus::Failed };
		std::optional<Scenario> scenario{};
	};

	LoadResult getScenario();
} // namespace scenario::loader
