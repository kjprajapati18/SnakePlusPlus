#include "Vector2D.h"

Vector2D& Vector2D::add(const Vector2D& v) {
	x += v.x;
	y += v.y;

	return *this;
}
Vector2D& Vector2D::subtract(const Vector2D& v){
	x -= v.x;
	y += v.y;

	return *this;
}
Vector2D& Vector2D::multiply(const Vector2D& v){
	x *= v.x;
	y *= v.y;

	return *this;
}
Vector2D& Vector2D::divide(const Vector2D& v){
	x /= v.x;
	y /= v.y;

	return *this;
}


Vector2D& operator*(Vector2D& v, float scalar) {
	v.x *= scalar;
	v.y *= scalar;
	return v;
}
Vector2D& operator/(Vector2D& v, float scalar) {
	v.x /= scalar;
	v.y /= scalar;
	return v;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2){
	return v1.add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2){
	return v1.subtract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2){
	return v1.multiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2){
	return v1.divide(v2);
}


Vector2D& Vector2D::operator+=(const Vector2D& v2){
	return this->add(v2);
}
Vector2D& Vector2D::operator-=(const Vector2D& v2){
	return this->subtract(v2);
}
Vector2D& Vector2D::operator*=(const Vector2D& v2){
	return this->multiply(v2);
}
Vector2D& Vector2D::operator/=(const Vector2D& v2){
	return this->divide(v2);
}


std::ostream& operator<<(std::ostream& stream, const Vector2D& v) {
	return stream << "(" << v.x << ", " << v.y << ")";
}