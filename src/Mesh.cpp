#include "pch.h"

#include "Mesh.h"

Mesh::Mesh() :
	positions(),
	normals(),
	texCoords(),
	face(),
	primitive_type(0),
	has_color(false),
	color(0),
	material_index(0)
{

}

Mesh::~Mesh()
{

}