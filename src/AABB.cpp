#include "pch.h"
#include "AABB.h"

AABB::AABB():
	xMin(0),
	xMax(0),
	yMin(0),
	yMax(0),
	zMin(0),
	zMax(0)
{

}

AABB::AABB(f32 xMin, f32 xMax, f32 yMin,
	f32 yMax, f32 zMin, f32 zMax):
	xMin(xMin),
	xMax(xMax),
	yMin(yMin),
	yMax(yMax),
	zMin(zMin),
	zMax(zMax)
{

}

AABB::~AABB()
{

}

bool AABB::checkIntersection(vec3 position)
{
	return (position.x >= xMin && position.x <= xMax) &&
		(position.y >= yMin && position.y <= yMax) &&
		(position.z >= zMin && position.z <= zMax);

	return false;
}