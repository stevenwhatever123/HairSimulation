#include "pch.h"
#include "Strand.h"

Strand::Strand():
	springs()
{

}

Strand::~Strand()
{

}

void Strand::create_bending_springs(f32 stiffness, f32 damping)
{
	// Create bending springs from existing mass points
	for (u32 i = 0; i < springs.size(); i++)
	{
		if (i >= springs.size() - 1)
			break;

		MassPoint* p1 = springs[i]->getMassPointOne();
		MassPoint* p2 = springs[i + 1]->getMassPointTwo();

		Spring* bending_spring = new Spring(p1, p2, false, stiffness, damping);

		bending_springs.push_back(bending_spring);
	}
}

void Strand::create_torsion_springs(f32 stiffness, f32 damping)
{
	// Create torsion spring from existing mass points
	for (u32 i = 0; i < springs.size(); i++)
	{
		if (i >= springs.size() - 2)
			break;

		MassPoint* p1 = springs[i]->getMassPointOne();
		MassPoint* p2 = springs[i + 2]->getMassPointTwo();

		Spring* torsion_spring = new Spring(p1, p2, true, stiffness, damping);

		torsion_springs.push_back(torsion_spring);
	}
}

void Strand::update(f32 dt)
{
	//for (Spring* spring : springs)
	//{
	//	spring->getMassPointOne()->resetSpringForce();
	//	spring->getMassPointTwo()->resetSpringForce();
	//}

	for (Spring* spring : springs)
	{
		spring->update(dt);

		spring->getMassPointOne()->addSpringForce(spring->getP1TotalForce());
		spring->getMassPointTwo()->addSpringForce(spring->getP2TotalForce());
	}
}

void Strand::update_bending(f32 dt)
{
	for (Spring* spring : bending_springs)
	{
		spring->update(dt);

		spring->getMassPointOne()->addSpringForce(spring->getP1TotalForce());
		spring->getMassPointTwo()->addSpringForce(spring->getP2TotalForce());
	}
}

void Strand::update_torsion(f32 dt)
{
	for (Spring* spring : torsion_springs)
	{
		spring->update(dt);

		spring->getMassPointOne()->addSpringForce(spring->getP1TotalForce());
		spring->getMassPointTwo()->addSpringForce(spring->getP2TotalForce());
	}
}

void Strand::updateImproved(f32 dt)
{
	// Normal springs update
	update(dt);

	update_bending(dt);
	update_torsion(dt);
}