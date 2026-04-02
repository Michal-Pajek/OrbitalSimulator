#include "input/Keyboard.hpp"
#include <cctype>

#ifdef _WIN32

#include <conio.h>

char getSingleKey()
{
    return static_cast<char>(std::toupper(static_cast<unsigned char>(_getch())));
}

#else

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <stdexcept>

namespace
{
    class TerminalRawModeGuard
    {
    public:
        TerminalRawModeGuard()
        {
            if (tcgetattr(STDIN_FILENO, &m_oldAttr) == -1) {
                throw std::runtime_error("tcgetattr failed");
            }

            termios newAttr{ m_oldAttr };
            newAttr.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));

            if (tcsetattr(STDIN_FILENO, TCSANOW, &newAttr) == -1) {
                throw std::runtime_error("tcsetattr failed");
            }

            m_active = true;
        }

        TerminalRawModeGuard(const TerminalRawModeGuard&) = delete;
        TerminalRawModeGuard& operator=(const TerminalRawModeGuard&) = delete;

        ~TerminalRawModeGuard()
        {
            if (m_active) {
                tcsetattr(STDIN_FILENO, TCSANOW, &m_oldAttr);
            }
        }

    private:
        termios m_oldAttr{};
        bool m_active{ false };
    };
} // anonymous namespace

char getSingleKey()
{
    TerminalRawModeGuard rawModeGuard{};

    const int ch{ std::getchar() };
    if (ch == EOF) {
        throw std::runtime_error("getchar failed");
    }

    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

#endif