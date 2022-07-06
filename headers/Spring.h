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

public:

public:
	Spring();
	Spring(MassPoint* p1, MassPoint* p2, float ks, float restLength, float kd);

	~Spring();
};