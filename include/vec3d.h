#ifndef  VEC3D_H
#define VEC3D_H

#include <iostream>

class vec2 {
public:
	vec2();

	vec2(double x, double y);

	double x, y;

	double getX();
	double getY();

	void setX(double x);
	void setY(double y);
};

class vec3 {
public:

	vec3();

	vec3(double x, double y, double z);

	double getX();
	double getY();
	double getZ();
	double getLenght();

	void setX(double x);
	void setY(double y);
	void setZ(double z);
	
	vec3 operator +(vec3 v);
	vec3 operator -(vec3 v);
	vec3 operator *(double k);
	vec3 operator /(double k);

	void operator+=(vec3 v);
	void operator-=(vec3 v);
	void operator*=(vec3 v);
	void operator/=(vec3 v);

	friend std::ostream& operator<<(std::ostream& os, const vec3& v);

	double x, y, z;
	double length;
};

// Cross product
vec3 cross(vec3 a, vec3 b);

double angle(vec3 a, vec3 b);

vec3 normalize(vec3 v);





#endif // ! VEC3D_H