#pragma once
#include "Types.h"

#include "Mesh.h"

class HairManager
{
private:

public:

	std::vector<vec3> hairRootPositions;
	std::vector<vec3> hairRootNormals;
	std::vector<vec2> hairRootTexCoords;
	std::vector<u32> hairRootIndicies;

public:
	HairManager();
	~HairManager();

	void generateHairRoots(const Mesh* mesh);

	Mesh* getHairRootAsMeshes();
};

