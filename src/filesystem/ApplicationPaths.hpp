#pragma once
#include <filesystem>

namespace filesystem::paths
{
	const std::filesystem::path& executableDirectory();
	std::filesystem::path scenariosDirectory();
	std::filesystem::path simulationsDirectory();
} // namespace filesystem::paths
