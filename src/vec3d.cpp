#include "vec3d.h"
#include <math.h>

vec3::vec3() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	length = 0.0;
}

vec3::vec3(double x, double y, double z)
	: x(x), y(y), z(z) {
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double vec3::getX() { return x; }
double vec3::getY() { return y; }
double vec3::getZ() { return z; }
double vec3::getLenght() { return length; }

void vec3::setX(double x) { 
	x = x; 
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
void vec3::setY(double y) { 
	y = y;
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
void vec3::setZ(double z) { 
	z = z; 
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

vec3 vec3::operator +(vec3 v) {
	return vec3(
		x + v.getX(),
		y + v.getY(),
		z + v.getZ()
	);
}

vec3 vec3::operator -(vec3 v) {
	return vec3(
		x - v.getX(),
		y - v.getY(),
		z - v.getZ()
	);
}

vec3 vec3::operator *(double k) {
	return vec3(
		x * k,
		y * k,
		z * k
	);
}

vec3 vec3::operator /(double k) {
	return vec3(
		x / k,
		y / k,
		z / k
	);
}

void vec3::operator+=(vec3 v) {
	x += v.getX();
	y += v.getY();
	z += v.getZ();
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void vec3::operator-=(vec3 v) {
	x -= v.getX();
	y -= v.getY();
	z -= v.getZ();
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void vec3::operator*=(vec3 v) {
	x *= v.getX();
	y *= v.getY();
	z *= v.getZ();
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void vec3::operator/=(vec3 v) {
	x /= v.getX();
	y /= v.getY();
	z /= v.getZ();
	length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

std::ostream& operator<<(std::ostream& os, const vec3& v) {
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	return os;
}

// Cross product
vec3 cross(vec3 a, vec3 b) {
	return vec3(
		a.getY() * b.getZ() - a.getZ() * b.getY(),
		a.getZ() * b.getX() - a.getX() * b.getZ(),
		a.getX() * b.getY() - a.getY() * b.getX()
	);
}

// Angulo entre 2 vectores
/*
double angle(vec3 a, vec3 b) {
	return acos((a * b) / (a.getLenght() + b.getLenght()));
}*/

vec3 normalize(vec3 v) {
	return v / v.getLenght();
}



vec2::vec2() {
	x = 0;
	y = 0;
}

vec2::vec2(double x, double y) {
	this->x = x;
	this->y = y;
}

double vec2::getX() {
	return x;
}

double vec2::getY() {
	return y;
}

void vec2::setX(double x) {
	this->x = x;
}

void vec2::setY(double y) {
	this->y = y;
}
