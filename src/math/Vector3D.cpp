#include "math/Vector3D.hpp"

#include <cmath>

#include "common/runtime_checks/RuntimeChecks.hpp"

Vector3D::Vector3D(double x, double y, double z) : m_x{ x }, m_y{ y }, m_z{ z }
{
	RuntimeChecks::ensure(std::isfinite(x) && std::isfinite(y) && std::isfinite(z), RuntimeChecks::Type::Argument, "All components of the vector must be finite");
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
	const Vector3D result{
		m_x + other.m_x,
		m_y + other.m_y,
		m_z + other.m_z
	};
	*this = result;
	return *this;
}

Vector3D Vector3D::operator/(const double scalar) const
{
	RuntimeChecks::ensure(scalar != 0.0, RuntimeChecks::Type::Argument, "Division of Vector3D by zero");
	return *this * (1.0 / scalar);
}

Vector3D Vector3D::operator-() const
{
	return Vector3D{ -m_x, -m_y, -m_z };
}

bool operator==(const Vector3D& vecA, const Vector3D& vecB)
{
	return vecA.m_x == vecB.m_x && vecA.m_y == vecB.m_y && vecA.m_z == vecB.m_z;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
	os << '[' << vec.m_x << "; " << vec.m_y << "; " << vec.m_z << ']';
	return os;
}

Vector3D operator*(const Vector3D& vec, const double scalar)
{
	return Vector3D{ scalar * vec.m_x, scalar * vec.m_y, scalar * vec.m_z };
}

Vector3D operator*(const double scalar, const Vector3D& vec)
{
	return Vector3D{ scalar * vec.m_x, scalar * vec.m_y, scalar * vec.m_z };
}

Vector3D operator-(const Vector3D& vecA, const Vector3D& vecB)
{
	return Vector3D{ vecA.m_x - vecB.m_x, vecA.m_y - vecB.m_y, vecA.m_z - vecB.m_z };
}

Vector3D operator+(const Vector3D& vecA, const Vector3D& vecB)
{
	return Vector3D{ vecA.m_x + vecB.m_x, vecA.m_y + vecB.m_y, vecA.m_z + vecB.m_z };
}
