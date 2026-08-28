#include "scenario/input/ScenarioInput.hpp"

#include "scenario/core/Scenario.hpp"

#include "body/input/BodyBuilder.hpp"
#include "input/data/DataGetter.hpp"
#include "localization/core/TextId.hpp"
#include "ui/ConsoleWriter.hpp"

namespace scenario::input
{
	std::string promptForScenarioName()
	{
		ui::console::write(localization::TextId::EnterScenarioName, ": ");
		return ::input::data::getFileBaseName();
	}

	std::vector<body::Body> createBodiesFromInput()
	{
		std::vector<body::Body> result{};
		ui::console::writeLine();
		ui::console::write(localization::TextId::EnterObjectCountNotGreaterThan, ' ', Scenario::MAX_BODY_COUNT, ": ");
		const auto bodiesCount{ static_cast<unsigned int>(::input::data::getValue<int>([](const int x) {return x > 0 && x <= static_cast<int>(Scenario::MAX_BODY_COUNT); })) };
		result.reserve(bodiesCount);
		for (unsigned int i{}; i < bodiesCount; ++i) {
			const body::input::BodyBuilder bodyBuilder{ result };
			result.emplace_back(bodyBuilder.createBodyFromInput());
		}

		return result;
	}
} // namespace scenario::input
