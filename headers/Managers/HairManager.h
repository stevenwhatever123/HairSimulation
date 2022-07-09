#pragma once
#include "Types.h"

#include "MassPoint.h"
#include "Mesh.h"
#include "Spring.h"

class HairManager
{
private:

	Mesh* hair_springs_meshes;

public:

	i32 numMassPointPerStrand = 8;

	f32 stiffness = 100.0f;
	f32 damping = 2.5f;

	std::vector<MassPoint*> mass_points;
	std::vector<Spring*> springs;

public:
	HairManager();
	~HairManager();

	void update(float dt);

	void generateHairRootMassPoints(const Mesh* mesh);

	void generateHairStrandMassPoints(u32 mass_point_per_strand);

	Mesh* getHairStrandSpringsAsMeshes();
	void updateHairStrandSpringMesh();

	void setStiffness(f32 stiffness);
	void setDamping(f32 damping);
	void restart();
};