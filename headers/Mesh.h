#pragma once
#include "Types.h"

class Mesh
{
public:
	std::string name;

	bool isMesh;
	bool isSkull;
	bool isMassPoint;

	// This will only use when isMassPoint is true
	u32 mass_point_id;

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