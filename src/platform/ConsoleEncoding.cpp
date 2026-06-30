#include "platform/ConsoleEncoding.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

namespace ConsoleEncoding
{
	void configureUtf8()
	{
#ifdef _WIN32
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);
#endif
	}
}
