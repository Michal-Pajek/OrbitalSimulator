#include "filesystem/ApplicationPaths.hpp"
#include <stdexcept>
#include <string>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

namespace
{
	namespace fs = std::filesystem;

	fs::path resolveExecutableDirectory()
	{
#ifdef _WIN32
		std::wstring buffer(32768, L'\0');

		const auto length{ GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size())) };

		if (length == 0 || length == buffer.size()) {
			throw std::runtime_error{ "Failed to determine executable path" };
		}

		buffer.resize(length);

		return fs::path{ buffer }.parent_path();

#elif defined(__linux__)
		return fs::read_symlink("/proc/self/exe").parent_path();

#else
#error Executable directory resolution is not implemented for this platform
#endif
	}
} // anonymous namespace

namespace ApplicationPaths
{
	const std::filesystem::path& executableDirectory()
	{
		static const fs::path directory{ resolveExecutableDirectory() };
		return directory;
	}

	fs::path scenariosDirectory()
	{
		return executableDirectory() / "scenarios";
	}

	fs::path simulationsDirectory()
	{
		return executableDirectory() / "simulations";
	}
} // ApplicationPaths
