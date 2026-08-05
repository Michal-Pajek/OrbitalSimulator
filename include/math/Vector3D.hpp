#pragma once
#include <cmath>
#include <ostream>

class Vector3D
{
	friend bool operator==(const Vector3D& vecA, const Vector3D& vecB);
	friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec);
	friend Vector3D operator*(const Vector3D& vec, const double scalar);
	friend Vector3D operator*(const double scalar, const Vector3D& vec);
	friend Vector3D operator-(const Vector3D& vecA, const Vector3D& vecB);
	friend Vector3D operator+(const Vector3D& vecA, const Vector3D& vecB);
public:
	Vector3D() = default;
	Vector3D(double x, double y, double z);
	double getX() const { return m_x; }
	double getY() const { return m_y; }
	double getZ() const { return m_z; }
	double getLength() const { return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }
	void setX(const double x) { m_x = x; }
	void setY(const double y) { m_y = y; }
	void setZ(const double z) { m_z = z; }
	Vector3D& operator+=(const Vector3D& other);
	Vector3D operator/(const double scalar) const;
	Vector3D operator-() const;
private:
	double m_x{};
	double m_y{};
	double m_z{};
};