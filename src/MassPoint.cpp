#include "pch.h"
#include "MassPoint.h"

MassPoint::MassPoint():
	position(0),
	normal(0),
	texCoord(0),
	velocity(0),
	force(0),
	springForce(0),
	mass(0),
	hairRoot(false),
	foreHead(false),
	primitive(0)
{

}

MassPoint::MassPoint(vec3 position, float mass) :
	position(position),
	normal(0),
	texCoord(0),
	velocity(0),
	springForce(0),
	force(0),
	mass(mass),
	hairRoot(false),
	foreHead(false),
	primitive(0)
{

}

MassPoint::MassPoint(vec3 position, vec3 normal, vec2 texCoord, float mass, bool isHairRoot, bool foreHead) :
	position(position),
	normal(normal),
	texCoord(texCoord),
	velocity(0),
	force(0),
	mass(mass),
	hairRoot(isHairRoot),
	foreHead(foreHead),
	primitive(0)
{

}

MassPoint::~MassPoint()
{

}

void MassPoint::moveDown()
{
	position.y -= 0.0001f;
}

void MassPoint::update(float dt)
{
	// Reset force
	force.x = 0;
	force.y = 0;
	force.z = 0;

	vec3 gravity(0, -9.8f, 0);

	force += gravity * mass + springForce;

	velocity += (force * dt) / mass;

	position += velocity * dt;
}

void MassPoint::resetSpringForce()
{
	this->springForce = vec3(0, 0, 0);
}

void MassPoint::resetAll()
{
	force = vec3(0);

	velocity = vec3(0);
}

void MassPoint::addSpringForce(vec3 force)
{
	this->springForce += force;
}

void MassPoint::move(vec3 direction, f32 distance)
{
	this->position = this->position + (direction * distance);
}

void MassPoint::collided()
{
	this->velocity = this->velocity / -5.0f;
}

void MassPoint::stop()
{
	hairRoot = true;
}

vec3 MassPoint::getPosition() const
{
	return this->position;
}

vec3 MassPoint::getNormal() const
{
	return this->normal;
}

vec2 MassPoint::getTexCoord() const
{
	return this->texCoord;
}

bool MassPoint::isHairRoot() const
{
	return this->hairRoot;
}

bool MassPoint::isForeHead() const
{
	return this->foreHead;
}

f32 MassPoint::getMass() const
{
	return this->mass;
}

vec3 MassPoint::getVelocity() const
{
	return this->velocity;
}