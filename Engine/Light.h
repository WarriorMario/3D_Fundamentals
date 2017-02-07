#pragma once
#include "Vec3.h"
#include "Colors.h"

class Light
{
public:
	Light(Vec3 pos, FColor col)
		:
		position(pos),
		color(col)
	{}
	Vec3 position;
	FColor color;
};