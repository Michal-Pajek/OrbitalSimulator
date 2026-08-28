#include "input/core/Keyboard.hpp"

#include <cctype>

#ifdef _WIN32

#include <conio.h>

#else

#include <termios.h>
#include <unistd.h>
#include <cstdio>

#include "common/runtime_checks/RuntimeChecks.hpp"

#endif

namespace input::keyboard
{

#ifdef _WIN32

    char getSingleKey()
    {
        return static_cast<char>(std::toupper(static_cast<unsigned char>(_getch())));
    }

#else

    namespace
    {
        class TerminalRawModeGuard
        {
        public:
            TerminalRawModeGuard()
            {
                runtime_checks::ensure(tcgetattr(STDIN_FILENO, &m_oldAttr) != -1, runtime_checks::Type::Runtime, "tcgetattr failed");

                termios newAttr{ m_oldAttr };
                newAttr.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));

                runtime_checks::ensure(tcsetattr(STDIN_FILENO, TCSANOW, &newAttr) != -1, runtime_checks::Type::Runtime, "tcsetattr failed");

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
        runtime_checks::ensure(ch != EOF, runtime_checks::Type::Runtime, "getchar failed");

        return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }

#endif

} // namespace input::keyboard
