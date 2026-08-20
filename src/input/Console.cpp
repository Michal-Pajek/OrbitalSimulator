#include "input/Console.hpp"

#include <cstdlib>

namespace Console
{
    void clearScreen()
    {

#ifdef _WIN32

        std::system("cls");

#else

        std::system("clear");

#endif

    }
} // namespace Console
