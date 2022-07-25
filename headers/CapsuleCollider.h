#pragma once
#include <Types.h>

#include <MassPoint.h>

class CapsuleCollider
{
private:
	vec3 tip;
	vec3 base;

	vec3 center;

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
	CapsuleCollider(vec3 center, f32 radius, f32 length, vec3 direction);

	~CapsuleCollider();

	void printInformation();

	void updatePositionByTransformation();

	bool checkCollision(MassPoint* mass_point);
	void collisionResponse(MassPoint* mass_point);

	void update();
};