#include "pch.h"
#include "Spring.h"

Spring::Spring():
	p1(nullptr),
	p2(nullptr),
	ks(0),
	restLength(0),
	kd(0),
	springForce(0),
	dampForce(0),
	totalForce(0),
	p1SpringForce(0),
	p2SpringForce(0),
	p1DampForce(0),
	p2DampForce(0),
	p1TotalForce(0),
	p2TotalForce(0)
{

}

Spring::Spring(MassPoint* p1, MassPoint* p2, float ks, float kd):
	p1(p1),
	p2(p2),
	ks(ks),
	restLength(0),
	kd(kd),
	springForce(0),
	dampForce(0),
	totalForce(0),
	p1SpringForce(0),
	p2SpringForce(0),
	p1DampForce(0),
	p2DampForce(0),
	p1TotalForce(0),
	p2TotalForce(0)
{
	this->restLength = glm::distance(p2->getPosition(), p1->getPosition());

	//float differenceBetweenTwoLength = glm::distance(p2->getPosition(), p1->getPosition());
	//this->springForce = ks * differenceBetweenTwoLength;

	//this->dampForce = glm::dot(glm::normalize(p2->getPosition() - p1->getPosition()), (p2->getVelocity() - p1->getVelocity())) * kd;

	//this->totalForce = this->springForce = this->dampForce;

}

Spring::~Spring()
{

}

void Spring::update(float dt)
{
	// Find the difference between two mass point and the rest length
	float differenceBetweenTwoLength = glm::distance(p1->getPosition(), p2->getPosition()) - this->restLength;

	vec3 directionToP1 = glm::normalize(p1->getPosition() - p2->getPosition());
	vec3 directionToP2 = glm::normalize(p2->getPosition() - p1->getPosition());

	p2SpringForce = ks * (differenceBetweenTwoLength * directionToP1);

	float length = glm::dot((p1->getVelocity() - p2->getVelocity()), directionToP1);

	p2DampForce = kd * length * directionToP1;

	p2TotalForce = p2SpringForce + p2DampForce;
	p1TotalForce = -p2TotalForce;
}

MassPoint* Spring::getMassPointOne()
{
	return p1;
}

MassPoint* Spring::getMassPointTwo()
{
	return p2;
}

vec3 Spring::getP1TotalForce() const
{
	return this->p1TotalForce;
}

vec3 Spring::getP2TotalForce() const
{
	return this->p2TotalForce;
}

f32 Spring::getP1MoveForce() const
{
	return this->p1MoveForce;
}

f32 Spring::getP2MoveForce() const
{
	return this->p2MoveForce;
}