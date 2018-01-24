#pragma once
#include <cmath>

struct Vec2i;
struct Vec3f;
struct Vec3i;
struct vec4float;

struct Vec2i {
	Vec2i(int x, int y) : x(x), y(y) {};
	Vec2i() : x(0), y(0) {};
	int x, y;

	Vec2i operator+ (Vec2i r) { return Vec2i(x + r.x, y + r.y); };
	Vec2i operator- (Vec2i r) { return Vec2i(x - r.x, y - r.y); };
	Vec2i operator* (float r) { return Vec2i(x*r, y*r); };
};

struct Vec3i {
	Vec3i(int x, int y, int z) : x(x), y(y), z(z) {};
	Vec3i() : x(0), y(0), z(0) {};
	//Vec3i(Vec3f vec) : x(vec.x), y(vec.y), z(vec.z) {};

	int x, y, z;

	//Vec3f operator+ (Vec3f r) { return Vec3f(x + r.x, y + r.y, z + r.z); };

	Vec3i operator- (Vec3i r) { return Vec3i(x - r.x, y - r.y, z - r.z); };
};

struct Vec3f {
	Vec3f() : x(0), y(0), z(0) {};
	Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};
	Vec3f(Vec3i vec) { x = vec.x; y = vec.y, z = vec.z; };

	void norm() { //нормализует вектор, т.е. делаем его длину равной единице
		float vecLen = sqrt(x*x + y*y + z*z);
		float invLen = 1 / vecLen;
		x = invLen*x;
		y = invLen*y;
		z = invLen*z;
	};

	float x, y, z;

	Vec3f operator+ (Vec3f r) { return Vec3f(x + r.x, y + r.y, z + r.z); };
	Vec3f operator- (Vec3f r) { return Vec3f(x - r.x, y - r.y, z - r.z); };
	Vec3f operator^ (Vec3f r) { return Vec3f(y*r.z - r.y*z, x*r.z - r.x*z, x*r.y - r.x*y); }; // векторное произведение
	Vec3f operator* (float r) { return Vec3f(x*r, y*r, z*r); }; //вектор на число
	float operator* (Vec3f r) { return x*r.x + y*r.y + z*r.z; }; //скаляр	
};

Vec3i ToVec3i(Vec3f vec);

