#pragma once
#include "Types.h"

#include "MassPoint.h"
#include "Mesh.h"

class HairManager
{
private:

public:

	std::vector<MassPoint*> mass_points;

public:
	HairManager();
	~HairManager();

	void generateHairRootMassPoints(const Mesh* mesh);

	std::vector<Mesh*> getHairRootMassPointsAsMeshes();
};