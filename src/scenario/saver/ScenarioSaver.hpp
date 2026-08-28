#pragma once
#include <string>

namespace scenario
{
	struct Scenario;

	namespace saver
	{
		enum class SaveResult {
			Saved,
			FileAlreadyExists
		};

		enum class OverwritePolicy {
			Deny,
			Allow
		};

		SaveResult save(const Scenario& scenario, const std::string& saveName, OverwritePolicy policy = OverwritePolicy::Deny);
		std::string getNextAvailableSaveName(const std::string& baseName);
	} // namespace saver
} // namespace scenario
