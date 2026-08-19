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
#include "app/ExceptionHandler.hpp"

namespace
{
    class TerminalRawModeGuard
    {
    public:
        TerminalRawModeGuard()
        {
            ExceptionHandler::ensure(tcgetattr(STDIN_FILENO, &m_oldAttr) != -1, ExceptionHandler::ExceptionType::Runtime, "tcgetattr failed");

            termios newAttr{ m_oldAttr };
            newAttr.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));

            ExceptionHandler::ensure(tcsetattr(STDIN_FILENO, TCSANOW, &newAttr) != -1, ExceptionHandler::ExceptionType::Runtime, "tcsetattr failed");

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
    ExceptionHandler::ensure(ch != EOF, ExceptionHandler::ExceptionType::Runtime, "getchar failed");

    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

#endif