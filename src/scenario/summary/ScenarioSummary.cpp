#include "scenario/summary/ScenarioSummary.hpp"

#include "scenario/core/Scenario.hpp"

#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace scenario::summary
{
	void print(const std::string_view name, const std::span<const body::Body> bodies)
	{
		ui::console::writeHeadline(localization::TextId::CurrentScenarioSummary);
		ui::console::writeLine(localization::TextId::ScenarioName, ":\t", name);
		ui::console::writeLine(localization::TextId::Bodies, ':');
		for (const auto& body : bodies) {
			body.printSummary(true);
		}
		ui::console::writeLine();
	}

	void print(const Scenario& scenario)
	{
		print(scenario.name, scenario.bodies);
	}
} // namespace scenario::summary
