#pragma once
#include "Types.h"

#include "MassPoint.h"
#include "Mesh.h"
#include "Spring.h"

class HairManager
{
private:

	u32 numMassPointPerStrand = 1;

	Mesh* hair_springs_meshes;

public:

	std::vector<MassPoint*> mass_points;
	std::vector<Spring*> springs;

public:
	HairManager();
	~HairManager();

	void update(float dt);

	void generateHairRootMassPoints(const Mesh* mesh);

	void generateHairStrandMassPoints();

	Mesh* getHairStrandSpringsAsMeshes();
	void updateHairStrandSpringMesh();
};