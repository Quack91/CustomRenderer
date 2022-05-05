#pragma once
#include <cmath>

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
	inline Vec2<T> operator *(T Value) { return Vec2<T>(x * Value, y * Value); }
	inline Vec2<T> operator /(T Value) { return Vec2<T>(x / Value, y / Value); }
	inline T operator [](int Index) { return raw[Index]; }

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

	inline Vec2<T>& operator *=(const T Value) {
		x *= Value;
		y *= Value;
		return *this;
	}

	inline Vec2<T>& operator /=(const T Value) {
		x /= Value;
		y /= Value;
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
template<class T>
struct Vec3
{
	union {
		struct { T x, y, z; };
		struct { T ivert, iuv, inorm; };
		T raw[3];
	};

	Vec3(T X = 0, T Y = 0, T Z = 0) : x(X), y(Y), z(Z) { }

	inline Vec3<T> operator +(const Vec3<T>& V) { return Vec3<T>(x + V.x, y + V.y, z + V.z); }
	inline Vec3<T> operator -(const Vec3<T>& V) { return Vec3<T>(x - V.x, y - V.y, z - V.z); }
	inline Vec3<T> operator *(T Value) { return Vec3<T>(x * Value, y * Value, z * Value); }
	inline Vec3<T> operator /(T Value) { return Vec3<T>(x / Value, y / Value, z/Value); }
	inline T operator [](int index) { return raw[index]; }

	inline Vec3<T>& operator +=(const Vec3<T>& V) {
		x += V.x;
		y += V.y;
		z += V.z;
		return *this;
	}

	inline Vec3<T>& operator -=(const Vec3<T>& V) {
		x -= V.x;
		y -= V.y;
		z -= V.z;
		return *this;
	}

	inline Vec3<T>& operator *=(const T Value) {
		x *= Value;
		y *= Value;
		z *= Value;
		return *this;
	}

	inline Vec3<T>& operator /=(const T Value) {
		x /= Value;
		y /= Value;
		z /= Value;
		return *this;
	}

	inline static float DotProduct(const Vec3<T>& lhs, const Vec3<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }

	inline float Length() {
		return std::sqrt(x * x + y * y + z*z);
	}

	inline Vec2<T> GetNormalized() {
		return *this / Length();
	}
};

typedef Vec2<float> Vector2;
typedef Vec2<int> Vector2Int;

typedef Vec3<float> Vector3;
typedef Vec3<int> Vector3Int;