#include <gtest/gtest.h>
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
        EXPECT_NO_THROW(ExceptionHandler::execute([] { throw std::runtime_error{ "Test exception" }; }));
    }

    TEST(ExceptionHandlerTests, ExecuteCatchesUnknownException)
    {
        EXPECT_NO_THROW(ExceptionHandler::execute([] { throw 42; }));
    }

} // anonymous namespace
