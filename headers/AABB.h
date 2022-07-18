#pragma once
#include "Types.h"

class AABB
{
private:

	f32 xMin;
	f32 xMax;
	f32 yMin;
	f32 yMax;
	f32 zMin;
	f32 zMax;

public:

	bool checkIntersection(vec3 position);

public:

	AABB();
	AABB(f32 xMin,
		f32 xMax,
		f32 yMin,
		f32 yMax,
		f32 zMin,
		f32 zMax);

	~AABB();

};

