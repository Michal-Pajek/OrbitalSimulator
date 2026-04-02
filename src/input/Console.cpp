#include "input/Console.hpp"
#include <cstdlib>

void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}