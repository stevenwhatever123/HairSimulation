#include "pch.h"

#include "Mesh.h"

Mesh::Mesh() :
	name(""),
	isMesh(false),
	isSkull(false),
	isHairRoot(false),
	positions(),
	normals(),
	texCoords(),
	indicies(),
	primitive_type(0),
	material_index(0)
{

}

Mesh::~Mesh()
{

}