#include "input/core/Console.hpp"

#include <cstdlib>

namespace input::console
{
    void clearScreen()
    {

#ifdef _WIN32

        std::system("cls");

#else

        std::system("clear");

#endif

    }
} // namespace input::console
