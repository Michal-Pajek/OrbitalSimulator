#include "simulation/run_config/builder/SimulationRunConfigBuilder.hpp"

#include <vector>

#include "input/data/DataGetter.hpp"
#include "input/selection/OptionSelector.hpp"
#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace simulation::run_config
{
	namespace
	{
		double promptForTimeStep()
		{
			ui::console::writeLine();
			const auto timeMultiplier{ input::selection::unit::selectUnitMultiplier(std::vector<input::selection::unit::UnitOption>{
				{localization::TextId::Second,	1.0},
				{localization::TextId::Minute,	60.0},
				{localization::TextId::Hour,	3600.0},
				{localization::TextId::Day,		86400.0}},
				localization::TextId::SelectTimeUnitForTimeStep) };
			ui::console::write(localization::TextId::EnterTimeStep, " (", localization::TextId::PositiveNumber, "): ");
			return timeMultiplier * input::data::getValue<double>([](const double x) { return x > 0.0; });
		}

		unsigned int promptForStepCount()
		{
			ui::console::write('\n', localization::TextId::EnterStepCount, ": ");
			return static_cast<unsigned int>(input::data::getValue<int>([](const int x) {return x > 0; }));
		}
	} // anonymous namespace

	SimulationRunConfig build()
	{
		const auto timeStep{ promptForTimeStep() };
		const auto stepCount{ promptForStepCount() };
		return SimulationRunConfig{ timeStep, stepCount };
	}
} // namespace simulation::run_config
