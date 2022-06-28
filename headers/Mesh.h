#pragma once
#include "Types.h"

class Mesh
{
public:
	std::vector<vec3> positions;
	std::vector<vec3> normals;
	std::vector<vec2> texCoords;
	std::vector<std::vector<u32>> face;

	u32 primitive_type;

	bool has_color;
	vec4 color;

	u32 material_index;

public:

	Mesh();
	~Mesh();

};