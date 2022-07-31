#include "pch.h"
#include "Strand.h"

Strand::Strand():
	springs()
{

}

Strand::~Strand()
{

}

void Strand::update(f32 dt)
{
	for (Spring* spring : springs)
	{
		spring->getMassPointOne()->resetSpringForce();
		spring->getMassPointTwo()->resetSpringForce();
	}

	for (Spring* spring : springs)
	{
		spring->update(dt);

		spring->getMassPointOne()->addSpringForce(spring->getP1TotalForce());
		spring->getMassPointTwo()->addSpringForce(spring->getP2TotalForce());
	}
}