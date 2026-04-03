#include "math/Vector3D.hpp"
#include <stdexcept>

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	m_z += other.m_z;
	return *this;
}

Vector3D Vector3D::operator/(const double cNumber) const
{
	if (cNumber == 0.0) {
		throw std::invalid_argument("Division of Vector2D by zero.");
	}
	return *this * (1.0 / cNumber);
}

Vector3D Vector3D::operator-() const
{
	return Vector3D{ -m_x, -m_y, -m_z };
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
	os << '[' << vec.m_x << "; " << vec.m_y << "; " << vec.m_z << ']';
	return os;
}

Vector3D operator*(const Vector3D& vec, const double cNumber)
{
	return Vector3D{ cNumber * vec.m_x, cNumber * vec.m_y, cNumber * vec.m_z };
}

Vector3D operator*(const double cNumber, const Vector3D& vec)
{
	return Vector3D{ cNumber * vec.m_x, cNumber * vec.m_y, cNumber * vec.m_z };
}

Vector3D operator-(const Vector3D& vecA, const Vector3D& vecB)
{
	return Vector3D{ vecA.m_x - vecB.m_x, vecA.m_y - vecB.m_y, vecA.m_z - vecB.m_z };
}

Vector3D operator+(const Vector3D& vecA, const Vector3D& vecB)
{
	return Vector3D{ vecA.m_x + vecB.m_x, vecA.m_y + vecB.m_y, vecA.m_z + vecB.m_z };
}