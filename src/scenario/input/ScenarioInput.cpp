#include "scenario/input/ScenarioInput.hpp"

#include "scenario/core/Scenario.hpp"

#include "input/data/DataGetter.hpp"
#include "localization/core/TextId.hpp"
#include "bodies/input/BodyBuilder.hpp"
#include "ui/ConsoleWriter.hpp"

namespace ScenarioInput
{
	std::string promptForScenarioName()
	{
		ConsoleWriter::write(TextId::EnterScenarioName, ": ");
		return DataGetter::getFileBaseName();
	}

	std::vector<Body> createBodiesFromInput()
	{
		std::vector<Body> result{};
		ConsoleWriter::writeLine();
		ConsoleWriter::write(TextId::EnterObjectCountNotGreaterThan, ' ', Scenario::MAX_BODY_COUNT, ": ");
		const auto bodiesCount{ static_cast<unsigned int>(DataGetter::getValue<int>([](const int x) {return x > 0 && x <= static_cast<int>(Scenario::MAX_BODY_COUNT); })) };
		result.reserve(bodiesCount);
		for (unsigned int i{}; i < bodiesCount; ++i) {
			const BodyBuilder bodyBuilder{ result };
			result.emplace_back(bodyBuilder.createBodyFromInput());
		}

		return result;
	}
} // namespace ScenarioInput
