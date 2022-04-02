#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float PI = 3.141592f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	/*�x���@ -> �ʓx�@*/
	inline float ToRadians(float degrees)
	{
		return degrees * PI / 180.0f;
	}

	/*�ʓx�@ -> �x���@*/
	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / PI;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template<typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template<typename T>
	T Clamp(const T& val, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, val));
	}

	inline float Abs(float val)
	{
		return fabs(val);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float angle)
	{
		return acosf(angle);
	}

	inline float Asin(float angle)
	{
		return asinf(angle);
	}

	inline float Atan(float angle)
	{
		return atanf(angle);
	}

	/*tan�̋t��*/
	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	inline float Sqrt(float val)
	{
		return sqrtf(val);
	}
}

class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		,y(0.0f)
	{}

	explicit Vector2(float inX, float inY)
		:x(inX)
		,y(inY)
	{}

	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	friend Vector2 operator*(const Vector2& a, float scalar)
	{
		return Vector2(a.x * scalar, a.y * scalar);
	}

	Vector2& operator+=(const Vector2& add)
	{
		x += add.x;
		y += add.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& subtract)
	{
		x -= subtract.x;
		y -= subtract.y;
		return *this;
	}

	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	/*�x�N�g���̑傫����2��*/
	float LengthSq() const
	{
		return (x * x + y * y);
	}

	/*�x�N�g���̑傫��*/
	float Length()
	{
		return (Math::Sqrt(LengthSq()));
	}

	/*�x�N�g���𐳋K������*/
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	/*�^����ꂽ�x�N�g���𐳋K�������l��Ԃ�*/
	static Vector2 Normalize(const Vector2& a)
	{
		Vector2 temp = a;
		temp.Normalize();
		return temp;
	}

	/*���`���*/
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(a + (b - a) * t);
	}

	/*����*/
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};