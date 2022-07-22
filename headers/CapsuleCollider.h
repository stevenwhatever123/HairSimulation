#pragma once
#include <Types.h>

class CapsuleCollider
{
private:
	vec3 tip;
	vec3 base;

	f32 radius;

	vec3 tipSphereCenter;
	vec3 baseSphereCenter;

	vec3 normal;
	vec3 lineEndOffset;

	// We may want to move this collider
	mat4 transformation;

public:

public:

	CapsuleCollider();
	CapsuleCollider(vec3 tip, vec3 base, f32 radius);

	~CapsuleCollider();

	void printInformation();

	void updatePositionByTransformation();

	void update();
};