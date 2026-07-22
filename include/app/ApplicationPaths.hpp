#pragma once
#include <filesystem>

namespace ApplicationPaths
{
	const std::filesystem::path& executableDirectory();
	std::filesystem::path scenariosDirectory();
	std::filesystem::path simulationsDirectory();
}
