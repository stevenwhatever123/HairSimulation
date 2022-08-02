#pragma once
#include "Types.h"

#include "MassPoint.h"

class Spring
{
private:

	// The two mass point the spring is linking to
	MassPoint* p1;
	MassPoint* p2;

	// Stiffness
	float ks;

	float restLength;

	// Damping factor
	float kd;

	float springForce;
	float dampForce;
	float totalForce;

	vec3 p1SpringForce;
	vec3 p2SpringForce;

	vec3 p1DampForce;
	vec3 p2DampForce;

	vec3 p1TotalForce;
	vec3 p2TotalForce;

	f32 p1MoveForce;
	f32 p2MoveForce;

public:

public:
	Spring();
	Spring(MassPoint* p1, MassPoint* p2, f32 ks, f32 kd);
	Spring(MassPoint* p1, MassPoint* p2, bool half, f32 ks, f32 kd);

	~Spring();

	void update(f32 dt);

	void setStiffness(f32 stiffness);
	void setDamping(f32 damping);

	// Getters
	MassPoint* getMassPointOne();
	MassPoint* getMassPointTwo();

	vec3 getP1TotalForce() const;
	vec3 getP2TotalForce() const;

	f32 getP1MoveForce() const;
	f32 getP2MoveForce() const;
};