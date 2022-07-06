#include "pch.h"
#include "Spring.h"

Spring::Spring():
	p1(nullptr),
	p2(nullptr),
	ks(0),
	restLength(0),
	kd(0)
{

}

Spring::Spring(MassPoint* p1, MassPoint* p2, float ks, float restLength, float kd):
	p1(p1),
	p2(p2),
	ks(ks),
	restLength(restLength),
	kd(kd)
{

}

Spring::~Spring()
{

}