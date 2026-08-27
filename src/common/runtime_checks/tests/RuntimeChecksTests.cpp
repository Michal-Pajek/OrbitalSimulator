#include <gtest/gtest.h>
#include <stdexcept>

#include "common/runtime_checks/RuntimeChecks.hpp"

namespace runtime_checks::tests
{
    TEST(RuntimeChecksTests, DoesNotThrowWhenConditionIsTrue)
    {
        EXPECT_NO_THROW(runtime_checks::ensure(true, Type::Runtime, "Test message"));
    }

    TEST(RuntimeChecksTests, ThrowsInvalidArgumentForArgumentType)
    {
        EXPECT_THROW(runtime_checks::ensure(false, Type::Argument, "Test message"), std::invalid_argument);
    }

    TEST(RuntimeChecksTests, ThrowsDomainErrorForDomainType)
    {
        EXPECT_THROW(runtime_checks::ensure(false, Type::Domain, "Test message"), std::domain_error);
    }

    TEST(RuntimeChecksTests, ThrowsLogicErrorForLogicType)
    {
        EXPECT_THROW(runtime_checks::ensure(false, Type::Logic, "Test message"), std::logic_error);
    }

    TEST(RuntimeChecksTests, ThrowsOutOfRangeForRangeType)
    {
        EXPECT_THROW(runtime_checks::ensure(false, Type::Range, "Test message"), std::out_of_range);
    }

    TEST(RuntimeChecksTests, ThrowsRuntimeErrorForRuntimeType)
    {
        EXPECT_THROW(runtime_checks::ensure(false, Type::Runtime, "Test message"), std::runtime_error);
    }

    TEST(RuntimeChecksTests, ThrowsLogicErrorForUnknownType)
    {
        const auto invalidType{ static_cast<Type>(999) };

        EXPECT_THROW(runtime_checks::ensure(false, invalidType, "Test message"), std::logic_error);
    }

    TEST(RuntimeChecksTests, PreservesExceptionMessage)
    {
        try {
            runtime_checks::ensure(false, Type::Runtime, "Expected message");
            FAIL() << "Expected exception was not thrown";
        }
        catch (const std::runtime_error& exception) {
            EXPECT_STREQ(exception.what(), "Expected message");
        }
    }
} // namespace runtime_checks::tests
