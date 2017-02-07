#pragma once
#include "Vec3.h"
#include "Colors.h"

class Sphere
{
public:
	Sphere(Vec3 position, float radius, FColor color)
		:
		position(position),
		radius(radius),
		color(color)
	{}
	Vec3 position;
	float radius;
	FColor color;
};