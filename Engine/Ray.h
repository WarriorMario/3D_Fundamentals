#pragma once
#include "Vec3.h"

class Sphere;
class Ray
{
public:
	Ray(Vec3 origin, Vec3 direction, float length)
		:
		origin(origin),
		direction(direction),
		length(length)
	{}

	bool RaySphereIntersection(const Sphere& sphere);

	Vec3 origin, direction;
	float length;
};