#include "math/Vector2D.hpp"
#include <stdexcept>

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	return *this;
}

Vector2D Vector2D::operator/(const double cNumber) const
{
	if (cNumber == 0.0) {
		throw std::invalid_argument("Division of Vector2D by zero.");
	}
	return *this * (1.0 / cNumber);
}

Vector2D Vector2D::operator-() const
{
	return Vector2D{ -m_x, -m_y };
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
	os << '[' << vec.m_x << "; " << vec.m_y << ']';
	return os;
}

Vector2D operator*(const Vector2D& vec, const double cNumber)
{
	return Vector2D{ cNumber * vec.m_x, cNumber * vec.m_y };
}

Vector2D operator*(const double cNumber, const Vector2D& vec)
{
	return Vector2D{ cNumber * vec.m_x, cNumber * vec.m_y };
}

Vector2D operator-(const Vector2D& vecA, const Vector2D& vecB)
{
	return Vector2D{ vecA.m_x - vecB.m_x, vecA.m_y - vecB.m_y };
}

Vector2D operator+(const Vector2D& vecA, const Vector2D& vecB)
{
	return Vector2D{ vecA.m_x + vecB.m_x, vecA.m_y + vecB.m_y };
}