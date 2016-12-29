#pragma once
#include "Vec3.h"

class Ray
{
public:
	Ray(Vec3 origin, Vec3 direction, float length)
		:
		origin(origin),
		direction(direction),
		length(length)
	{}
	Vec3 origin, direction;
	float length;
};