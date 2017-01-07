#include "Ray.h"
#include "Sphere.h"

bool Ray::RaySphereIntersection(const Sphere& sphere)
{
	Vec3 originToSphere = sphere.position - origin;
	float projection = Dot(originToSphere, direction);
	Vec3 distanceVector = originToSphere - direction*projection;
	float distanceSq = Dot(distanceVector, distanceVector);
	float radiusSq = sphere.radius*sphere.radius;

	if (distanceSq > radiusSq)
	{
		return false;
	}

	float newLength = projection - sqrtf(radiusSq-distanceSq);
	if (newLength < length&&newLength>0.0f)
	{
		length = newLength;
		return true;
	}
	return false;
}
