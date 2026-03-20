#include <gtest/gtest.h>
#include "math/Vector2D.hpp"

TEST(Vector2DTests, AdditionWorksCorrectly)
{
	const Vector2D a{ 1.0, 2.0 };
	const Vector2D b{ 3.0, 4.0 };
	const auto result{ a + b };
	EXPECT_DOUBLE_EQ(result.getX(), 4.0);
	EXPECT_DOUBLE_EQ(result.getY(), 6.0);
}

TEST(Vector2DTests, UnaryMinusWorksCorrectly)
{
	const Vector2D a{ 2.5, -7.0 };
	const auto result{ -a };
	EXPECT_DOUBLE_EQ(result.getX(), -2.5);
	EXPECT_DOUBLE_EQ(result.getY(), 7.0);
}

TEST(Vector2DTests, SubtractionWorksCorrectly)
{
	const Vector2D a{ 10.0, 4.0 };
	const Vector2D b{ 5.0, 8.0 };
	const auto result{ a - b };
	EXPECT_DOUBLE_EQ(result.getX(), 5.0);
	EXPECT_DOUBLE_EQ(result.getY(), -4.0);
}

TEST(Vector2DTests, MultiplicationWorksCorrectly)
{
	const Vector2D vec{ 6.0, 3.0 };
	const auto num{ 2.0 };
	const auto result1{ vec * num };
	const auto result2{ num * vec };
	EXPECT_DOUBLE_EQ(result1.getX(), 12.0);
	EXPECT_DOUBLE_EQ(result1.getY(), 6.0);
	EXPECT_DOUBLE_EQ(result2.getX(), 12.0);
	EXPECT_DOUBLE_EQ(result2.getY(), 6.0);
}

TEST(Vector2DTests, DivisionWorksCorrectly)
{
	const Vector2D vec{ 6.0, 9.0 };
	const auto num{ 3.0 };
	const auto result{ vec / num };
	EXPECT_DOUBLE_EQ(result.getX(), 2.0);
	EXPECT_DOUBLE_EQ(result.getY(), 3.0);
}

TEST(Vector2DTests, DivisionByZeroThrowsException)
{
	const Vector2D vec{ 6.0, 9.0 };
	EXPECT_THROW(vec / 0.0, std::invalid_argument);
}

TEST(Vector2DTests, ModulusWorksCorrectly)
{
	const Vector2D vec{ 3.0, 4.0 };
	const auto result{ vec.getLength() };
	EXPECT_DOUBLE_EQ(result, 5.0);
}