#pragma once
#include <math.h>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D() : x(0), y(0) {}
	Vector2D(float _x, float _y) : x(_x), y(_y) {}

	void set(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float length() { return sqrt(x * x + y * y); }

	void normalize()
	{
		int l = length();
		if (l > 0)
		{
			(*this) *= 1.0f / l;
		}
	}

	Vector2D operator+(const Vector2D& v2) const { return Vector2D(x + v2.x, y + v2.y); }
	Vector2D operator-(const Vector2D& v2) const { return Vector2D(x - v2.x, y - v2.y); }
	Vector2D operator*(float scalar) { return Vector2D(x * scalar, y * scalar); }
	Vector2D operator/(float scalar) { return Vector2D(x / scalar, y / scalar); }

	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;

		return v1;
	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;

		return v1;
	}
	Vector2D& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}
	Vector2D& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}
};