#include "pch.h"
#include "MassPoint.h"

MassPoint::MassPoint():
	position(0),
	normal(0),
	texCoord(0),
	velocity(0),
	force(0),
	mass(0),
	hairRoot(false),
	primitive(0)
{

}

MassPoint::MassPoint(vec3 position, float mass) :
	position(position),
	normal(0),
	texCoord(0),
	velocity(0),
	force(0),
	mass(mass),
	hairRoot(false),
	primitive(0)
{

}

MassPoint::MassPoint(vec3 position, vec3 normal, vec2 texCoord, float mass, bool isHairRoot) :
	position(position),
	normal(normal),
	texCoord(texCoord),
	velocity(0),
	force(0),
	mass(mass),
	hairRoot(isHairRoot),
	primitive(0)
{

}

MassPoint::~MassPoint()
{

}

void MassPoint::moveDown()
{
	position.y -= 0.01f;
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