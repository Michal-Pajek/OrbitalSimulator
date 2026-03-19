#pragma once
#include <cmath>
#include <ostream>

class Vector2D
{
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
	friend Vector2D operator*(const Vector2D& vec, const double cNumber);
	friend Vector2D operator*(const double cNumber, const Vector2D& vec);
	friend Vector2D operator-(const Vector2D& vecA, const Vector2D& vecB);
	friend Vector2D operator+(const Vector2D& vecA, const Vector2D& vecB);
public:
	Vector2D() = default;
	Vector2D(double x, double y) : m_x{ x }, m_y{ y } {}
	double getX() const { return m_x; }
	double getY() const { return m_y; }
	double getLength() const { return sqrt(m_x * m_x + m_y * m_y); }
	void setX(const double x) { m_x = x; }
	void setY(const double y) { m_y = y; }
	Vector2D& operator+=(const Vector2D& other);
	Vector2D operator/(const double cNumber) const;
	Vector2D operator-() const;
private:
	double m_x{};
	double m_y{};
};