#pragma once
#include "Types.h"

#include "MassPoint.h"
#include "Mesh.h"
#include "Spring.h"

class HairManager
{
private:

	u32 numMassPointPerStrand = 1;

public:

	std::vector<MassPoint*> mass_points;
	std::vector<Spring*> springs;

public:
	HairManager();
	~HairManager();

	void generateHairRootMassPoints(const Mesh* mesh);

	void generateHairStrandMassPoints();

	std::vector<Mesh*> getHairRootMassPointsAsMeshes();

	Mesh* getHairStrandSpringsAsMeshes();
	void generateHairStrandSpringsBuffers(Mesh* mesh);
	void updateHairStrandSpringMesh(Mesh* mesh);
};