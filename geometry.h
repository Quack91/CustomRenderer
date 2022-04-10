#pragma once

/*
* File containing linear algebra structures that describe geometry.
*/

template<class T>
struct Vec2
{
	union {
		struct { T x, y; };
		struct { T u, v; };
		T raw[2];
	};

	Vec2(T X = 0, T Y = 0) : x(X), y(Y) { }

	inline Vec2<T> operator +(const Vec2<T>& V) { return Vec2<T>(x + V.x, y + V.y); }
	inline Vec2<T> operator -(const Vec2<T>& V) { return Vec2<T>(x - V.x, y - V.y); }
	inline Vec2<T> operator *(T value) { return Vec2<T>(x * value, y * value); }
	inline Vec2<T> operator /(T value) { return Vec2<T>(x / value, y / value); }
	inline T operator [](int index) { return raw[index]; }

	inline Vec2<T>& operator +=(const Vec2<T>& V) {
		x += V.x;
		y += V.y;
		return *this;
	}

	inline Vec2<T>& operator -=(const Vec2<T>& V) {
		x -= V.x;
		y -= V.y;
		return *this;
	}

	inline Vec2<T>& operator *=(const T value) {
		x *= value;
		y *= value;
		return *this;
	}

	inline Vec2<T>& operator /=(const T value) {
		x /= value;
		y /= value;
		return *this;
	}

	inline static float DotProduct(const Vec2<T>& lhs, const Vec2<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

	inline float Length() {
		return std::sqrt(x * x + y * y);
	}

	inline Vec2<T> GetNormalized() {
		return *this / Length();
	}
};


typedef Vec2<float> Vector2;
typedef Vec2<int> Vector2Int;