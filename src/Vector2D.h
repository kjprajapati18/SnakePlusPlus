#pragma once
#include <iostream>
#include <math.h>

class Vector2D {
public:
	float x;
	float y;
	
	Vector2D(float xIn = 0, float yIn = 0):
		x(xIn), y(yIn)
	{}

	Vector2D& add(const Vector2D& v);
	Vector2D& subtract(const Vector2D& v);
	Vector2D& multiply(const Vector2D& v);
	Vector2D& divide(const Vector2D& v);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	friend Vector2D& operator*(Vector2D& v, float scalar);
	friend Vector2D& operator/(Vector2D& v, float scalar);

	Vector2D& operator+=(const Vector2D& v2);
	Vector2D& operator-=(const Vector2D& v2);
	Vector2D& operator*=(const Vector2D& v2);
	Vector2D& operator/=(const Vector2D& v2);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& v);

	void normalize() {
		float mag = sqrt(x*x + y*y);
		x /= mag;
		y /= mag;
	}
};