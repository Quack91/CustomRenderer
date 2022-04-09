#pragma once

/*
* File containing linear algebra structures that describe geometry.
*/

struct Vector2
{
	union
	{
		struct {
			float x, y;
		};
		struct {
			float u, v;
		};

		float raw[2];
	};

	Vector2(float X = 0, float Y = 0) : x(X), y(Y)
	{

	}

	inline Vector2 operator +(const Vector2& V) {
		return Vector2(x + V.x, y + V.y);
	}

	inline Vector2 operator -(const Vector2& V) {
		return Vector2(x - V.x, y - V.y);
	}

	inline Vector2 operator *(float f) {
		return Vector2(x * f, y * f);
	}

	inline Vector2 operator *(int i) {
		return Vector2(x * i, y * i);
	}

	inline float operator [](int index) {
		return raw[index];
	}

	inline float operator |(const Vector2& V) const {
		return x * V.x + y * V.y;
	}

	Vector2& operator *=(float f)
	{
		x *= f;
		y *= f;

		return *this;
	}

	Vector2& operator *=(int i)
	{
		x *= i;
		y *= i;

		return *this;
	}


	static float DotProduct(const Vector2& lhs, const Vector2& rhs) {
		return lhs | rhs;
	}
};