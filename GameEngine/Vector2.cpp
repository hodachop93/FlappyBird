#include "Vector2.h"
#include <math.h>

namespace gamerize
{
	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2::~Vector2()
	{
	}

	Vector2 Vector2::operator*(const float f)
	{
		return Vector2(x * f, y * f);
	}

	Vector2& Vector2::operator*=(const float f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	float Vector2::operator*(const Vector2 &v)
	{
		return x * v.x + y * v.y;
	}
	
	Vector2 Vector2::operator+(const Vector2 &v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2& Vector2::operator+=(const Vector2 &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	
	Vector2 Vector2::operator-()
	{
		return Vector2(-x, -y);
	}

	Vector2 Vector2::operator-(const Vector2 &v)
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2& Vector2::operator-=(const Vector2 &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2 Vector2::normalize()
	{
		float m = mag();
		return (*this) * m;
	}

	float Vector2::mag()
	{
		return sqrt(x * x + y * y);
	}

	void Vector2::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
}