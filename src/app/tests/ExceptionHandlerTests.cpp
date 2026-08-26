#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "app/ExceptionHandler.hpp"

namespace
{
    TEST(ExceptionHandlerTests, ExecuteRunsAction)
    {
        bool executed{ false };
        ExceptionHandler::execute([&executed] { executed = true; });

        EXPECT_TRUE(executed);
    }

    TEST(ExceptionHandlerTests, ExecuteCatchesStdException)
    {
        std::ostringstream output{};
        auto* originalBuffer{ std::cout.rdbuf(output.rdbuf()) };

        EXPECT_NO_THROW(ExceptionHandler::execute([] { throw std::runtime_error{ "Test exception" }; }));

        std::cout.rdbuf(originalBuffer);

        EXPECT_EQ(output.str(), "ERROR: Test exception\n");
    }

    TEST(ExceptionHandlerTests, ExecuteCatchesUnknownException)
    {
        std::ostringstream output{};
        auto* originalBuffer{ std::cout.rdbuf(output.rdbuf()) };

        EXPECT_NO_THROW(ExceptionHandler::execute([] { throw 42; }));

        std::cout.rdbuf(originalBuffer);

        EXPECT_EQ(output.str(), "ERROR: Unknown exception\n");
    }

} // anonymous namespace
