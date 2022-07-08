#pragma once
#include "Types.h"

class MassPoint
{
private:

	// Some common properties as the mesh, but we would normally
	// use the position only
	vec3 position;
	vec3 normal;
	vec2 texCoord;

	vec3 velocity;
	vec3 force;

	vec3 springForce;

	float mass;

	bool hairRoot;

	u32 primitive;

public:

public:

	MassPoint();
	MassPoint(vec3 position, float mass);
	MassPoint(vec3 position, vec3 normal, vec2 texCoord, float mass, bool isHairRoot);

	~MassPoint();

	void moveDown();

	void update(float dt);

	// Command call
	void resetSpringForce();

	// Setters
	void addSpringForce(vec3 force);

	// Getters
	vec3 getPosition() const;
	vec3 getNormal() const;
	vec2 getTexCoord() const;
	bool isHairRoot() const;
	f32 getMass() const;
	vec3 getVelocity() const;
};

