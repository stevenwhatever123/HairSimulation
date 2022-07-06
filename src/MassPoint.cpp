#include "pch.h"
#include "MassPoint.h"

MassPoint::MassPoint():
	position(0),
	normal(0),
	texCoord(0),
	velocity(0),
	force(0),
	mass(0),
	isHairRoot(false),
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
	isHairRoot(false),
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
	isHairRoot(isHairRoot),
	primitive(0)
{

}

MassPoint::~MassPoint()
{

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