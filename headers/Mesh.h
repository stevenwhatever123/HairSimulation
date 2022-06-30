#pragma once
#include "Types.h"

class Mesh
{
public:
	std::string name;

	std::vector<vec3> positions;
	std::vector<vec3> normals;
	std::vector<vec2> texCoords;
	std::vector<u32> indicies;

	u32 primitive_type;

	u32 material_index;

public:

	Mesh();
	~Mesh();

};