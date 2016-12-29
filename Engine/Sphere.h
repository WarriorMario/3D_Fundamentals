#pragma once
#include "Vec3.h"

class Sphere
{
public:
	Sphere(Vec3 position, float radius)
		:
		position(position),
		radius(radius)
	{}
	Vec3 position;
	float radius;
};