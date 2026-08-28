#include "scenario/summary/ScenarioSummary.hpp"

#include "scenario/core/Scenario.hpp"

#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace ScenarioSummary
{
	void print(const std::string_view name, const std::span<const body::Body> bodies)
	{
		ConsoleWriter::writeHeadline(localization::TextId::CurrentScenarioSummary);
		ConsoleWriter::writeLine(localization::TextId::ScenarioName, ":\t", name);
		ConsoleWriter::writeLine(localization::TextId::Bodies, ':');
		for (const auto& body : bodies) {
			body.printSummary(true);
		}
		ConsoleWriter::writeLine();
	}

	void print(const Scenario& scenario)
	{
		print(scenario.name, scenario.bodies);
	}
} // namespace ScenarioSummary
