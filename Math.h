#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float PI = 3.141592f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	/*度数法 -> 弧度法*/
	inline float ToRadians(float degrees)
	{
		return degrees * PI / 180.0f;
	}

	/*弧度法 -> 度数法*/
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

	/*tanの逆数*/
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

	/*ベクトルの大きさの2乗*/
	float LengthSq() const
	{
		return (x * x + y * y);
	}

	/*ベクトルの大きさ*/
	float Length()
	{
		return (Math::Sqrt(LengthSq()));
	}

	/*ベクトルを正規化する*/
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	/*与えられたベクトルを正規化した値を返す*/
	static Vector2 Normalize(const Vector2& a)
	{
		Vector2 temp = a;
		temp.Normalize();
		return temp;
	}

	/*線形補間*/
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(a + (b - a) * t);
	}

	/*内積*/
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