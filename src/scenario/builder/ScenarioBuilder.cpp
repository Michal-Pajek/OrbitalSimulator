#include "scenario/builder/ScenarioBuilder.hpp"

#include <optional>
#include <utility>

#include "scenario/editor/ScenarioEditor.hpp"
#include "scenario/input/ScenarioInput.hpp"

namespace scenario::builder
{
	std::optional<Scenario> buildScenario()
	{
		auto name{ input::promptForScenarioName() };
		auto bodies{ input::createBodiesFromInput() };
		ScenarioEditor editor{ {std::move(name), std::move(bodies)} };
		return editor.getReviewedScenario();
	}
} // namespace scenario::builder
