#include "app/ExceptionHandler.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

namespace
{
    using ExceptionHandler::ExceptionType;

    TEST(ExceptionHandlerTests, DoesNotThrowWhenConditionIsTrue)
    {
        EXPECT_NO_THROW(ExceptionHandler::ensure(true, ExceptionType::Runtime, "Test message"));
    }

    TEST(ExceptionHandlerTests, ThrowsInvalidArgumentForArgumentType)
    {
        EXPECT_THROW(ExceptionHandler::ensure(false, ExceptionType::Argument, "Test message"), std::invalid_argument);
    }

    TEST(ExceptionHandlerTests, ThrowsDomainErrorForDomainType)
    {
        EXPECT_THROW(ExceptionHandler::ensure(false, ExceptionType::Domain, "Test message"), std::domain_error);
    }

    TEST(ExceptionHandlerTests, ThrowsLogicErrorForLogicType)
    {
        EXPECT_THROW(ExceptionHandler::ensure(false, ExceptionType::Logic, "Test message"), std::logic_error);
    }

    TEST(ExceptionHandlerTests, ThrowsOutOfRangeForRangeType)
    {
        EXPECT_THROW(ExceptionHandler::ensure(false, ExceptionType::Range, "Test message"), std::out_of_range);
    }

    TEST(ExceptionHandlerTests, ThrowsRuntimeErrorForRuntimeType)
    {
        EXPECT_THROW(ExceptionHandler::ensure(false, ExceptionType::Runtime, "Test message"), std::runtime_error);
    }

    TEST(ExceptionHandlerTests, ThrowsLogicErrorForUnknownExceptionType)
    {
        const auto invalidType{ static_cast<ExceptionType>(999) };

        EXPECT_THROW(ExceptionHandler::ensure(false, invalidType, "Test message"), std::logic_error);
    }

    TEST(ExceptionHandlerTests, PreservesExceptionMessage)
    {
        try {
            ExceptionHandler::ensure(false, ExceptionType::Runtime, "Expected message");
            FAIL() << "Expected exception was not thrown";
        }
        catch (const std::runtime_error& exception) {
            EXPECT_STREQ(exception.what(), "Expected message");
        }
    }

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
