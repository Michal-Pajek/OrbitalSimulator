#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>

#include "math/Vector3D.hpp"

TEST(Vector3DTests, AdditionWorksCorrectly)
{
	const Vector3D a{ 1.0, 2.0, 5.0 };
	const Vector3D b{ 3.0, 4.0, 6.0 };
	const auto result{ a + b };
	EXPECT_DOUBLE_EQ(result.getX(), 4.0);
	EXPECT_DOUBLE_EQ(result.getY(), 6.0);
	EXPECT_DOUBLE_EQ(result.getZ(), 11.0);
}

TEST(Vector3DTests, UnaryMinusWorksCorrectly)
{
	const Vector3D a{ 2.5, -7.0, 4.2 };
	const auto result{ -a };
	EXPECT_DOUBLE_EQ(result.getX(), -2.5);
	EXPECT_DOUBLE_EQ(result.getY(), 7.0);
	EXPECT_DOUBLE_EQ(result.getZ(), -4.2);
}

TEST(Vector3DTests, SubtractionWorksCorrectly)
{
	const Vector3D a{ 10.0, 4.0, 2.0 };
	const Vector3D b{ 5.0, 8.0, 11.0 };
	const auto result{ a - b };
	EXPECT_DOUBLE_EQ(result.getX(), 5.0);
	EXPECT_DOUBLE_EQ(result.getY(), -4.0);
	EXPECT_DOUBLE_EQ(result.getZ(), -9.0);
}

TEST(Vector3DTests, MultiplicationWorksCorrectly)
{
	const Vector3D vec{ 6.0, 3.0, 1.0 };
	const auto num{ 2.0 };
	const auto result1{ vec * num };
	const auto result2{ num * vec };
	EXPECT_DOUBLE_EQ(result1.getX(), 12.0);
	EXPECT_DOUBLE_EQ(result1.getY(), 6.0);
	EXPECT_DOUBLE_EQ(result1.getZ(), 2.0);
	EXPECT_DOUBLE_EQ(result2.getX(), 12.0);
	EXPECT_DOUBLE_EQ(result2.getY(), 6.0);
	EXPECT_DOUBLE_EQ(result2.getZ(), 2.0);
}

TEST(Vector3DTests, DivisionWorksCorrectly)
{
	const Vector3D vec{ 6.0, 9.0, 3.0 };
	const auto num{ 3.0 };
	const auto result{ vec / num };
	EXPECT_DOUBLE_EQ(result.getX(), 2.0);
	EXPECT_DOUBLE_EQ(result.getY(), 3.0);
	EXPECT_DOUBLE_EQ(result.getZ(), 1.0);
}

TEST(Vector3DTests, DivisionByZeroThrowsException)
{
	const Vector3D vec{ 6.0, 9.0, 0.0 };
	EXPECT_THROW(vec / 0.0, std::invalid_argument);
}

TEST(Vector3DTests, ModulusWorksCorrectly)
{
	const Vector3D vec{ 3.0, 4.0, 0.0 };
	const auto result{ vec.getLength() };
	EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(Vector3DTests, ConstructorRejectsInfiniteComponent)
{
	constexpr auto positiveInfinity{ std::numeric_limits<double>::infinity() };
	constexpr auto negativeInfinity{ -positiveInfinity };

	for (const auto infinity : { positiveInfinity, negativeInfinity }) {
		EXPECT_THROW((Vector3D{ infinity, 0.0, 0.0 }), std::invalid_argument);
		EXPECT_THROW((Vector3D{ 0.0, infinity, 0.0 }), std::invalid_argument);
		EXPECT_THROW((Vector3D{ 0.0, 0.0, infinity }), std::invalid_argument);
	}
}

TEST(Vector3DTests, PlusEqualsPreservesStateWhenResultIsNotFinite)
{
	constexpr auto maxFinite{ std::numeric_limits<double>::max() };
	Vector3D vector{ maxFinite, 10.0, 20.0 };
	const Vector3D other{ maxFinite, 1.0, 2.0 };

	EXPECT_THROW(vector += other, std::invalid_argument);
	EXPECT_DOUBLE_EQ(vector.getX(), maxFinite);
	EXPECT_DOUBLE_EQ(vector.getY(), 10.0);
	EXPECT_DOUBLE_EQ(vector.getZ(), 20.0);
}

TEST(Vector3DTests, ConstructorRejectsNaNComponent)
{
	constexpr auto nan{ std::numeric_limits<double>::quiet_NaN() };
	EXPECT_THROW((Vector3D{ nan, 0.0, 0.0 }), std::invalid_argument);
	EXPECT_THROW((Vector3D{ 0.0, nan, 0.0 }), std::invalid_argument);
	EXPECT_THROW((Vector3D{ 0.0, 0.0, nan }), std::invalid_argument);
}
