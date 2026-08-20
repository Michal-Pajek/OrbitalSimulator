#include "simulation/SimulationRunConfigBuilder.hpp"

#include <vector>

#include "input/DataGetter.hpp"
#include "input/OptionSelector.hpp"
#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace SimulationRunConfigBuilder
{
	namespace
	{
		double promptForTimeStep()
		{
			ConsoleWriter::writeLine();
			const auto timeMultiplier{ UnitSelector::selectUnitMultiplier(std::vector<UnitSelector::UnitOption>{
				{TextId::Second,	1.0},
				{TextId::Minute,	60.0},
				{TextId::Hour,		3600.0},
				{TextId::Day,		86400.0}},
				TextId::SelectTimeUnitForTimeStep) };
			ConsoleWriter::write(TextId::EnterTimeStep, " (", TextId::PositiveNumber, "): ");
			return timeMultiplier * DataGetter::getValue<double>([](const double x) { return x > 0.0; });
		}

		unsigned int promptForStepCount()
		{
			ConsoleWriter::write('\n', TextId::EnterStepCount, ": ");
			return static_cast<unsigned int>(DataGetter::getValue<int>([](const int x) {return x > 0; }));
		}
	} // anonymous namespace

	SimulationRunConfig build()
	{
		const auto timeStep{ promptForTimeStep() };
		const auto stepCount{ promptForStepCount() };
		return SimulationRunConfig{ timeStep, stepCount };
	}
} // namespace SimulationRunConfigBuilder
