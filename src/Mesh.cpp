#include "pch.h"

#include "Mesh.h"

Mesh::Mesh() :
	name(),
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