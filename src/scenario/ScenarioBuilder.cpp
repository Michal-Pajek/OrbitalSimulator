#include "scenario/ScenarioBuilder.hpp"

#include <optional>
#include <utility>

#include "scenario/ScenarioEditor.hpp"
#include "scenario/input/ScenarioInput.hpp"

namespace ScenarioBuilder
{
	std::optional<Scenario> buildScenario()
	{
		auto name{ ScenarioInput::promptForScenarioName() };
		auto bodies{ ScenarioInput::createBodiesFromInput() };
		ScenarioEditor editor{ {std::move(name), std::move(bodies)} };
		return editor.getReviewedScenario();
	}
} // namespace ScenarioBuilder
