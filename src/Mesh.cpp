#include "pch.h"

#include "Mesh.h"

Mesh::Mesh() :
	name(""),
	isMesh(false),
	isSkull(false),
	isMassPoint(false),
	positions(),
	normals(),
	texCoords(),
	indicies(),
	primitive_type(0),
	material_index(0),
	mass_point_id(0)
{

}

Mesh::~Mesh()
{

}