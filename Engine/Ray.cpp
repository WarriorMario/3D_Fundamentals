#include "Ray.h"
#include "Sphere.h"

bool Ray::RaySphereIntersection(const Sphere& sphere)
{
	Vec3 originToSphere = sphere.position - origin;
	float projection = Dot(originToSphere, direction);
	Vec3 distanceVector = originToSphere - direction*projection;
	float distanceSq = Dot(distanceVector, distanceVector);
	
	if (distanceSq > sphere.radius*sphere.radius)
	{
		return false;
	}

	float newLength = sphere.radius - sqrtf(distanceSq);
	if (newLength < length&&newLength>0.0f)
	{
		length = newLength;
		return true;
	}
	return false;
}
