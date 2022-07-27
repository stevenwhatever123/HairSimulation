#pragma once
#include "Types.h"

#include "MassPoint.h"
#include "Mesh.h"
#include "Spring.h"
#include "Strand.h"

class HairManager
{
private:

	Mesh* hair_springs_meshes;

public:

	i32 numMassPointPerStrand = 8;

	f32 stiffness = 1.0f;
	f32 damping = 0.024f;

	//f32 stiffness = 5.0f;
	//f32 damping = 0.2f;

	std::vector<MassPoint*> mass_points;
	std::vector<Spring*> springs;
	std::vector<Strand*> strands;
	

public:
	HairManager();
	~HairManager();

	void update(float dt);

	void generateHairRootMassPoints(const Mesh* mesh);

	void generateHairStrandMassPoints(u32 mass_point_per_strand);

	Mesh* getHairStrandSpringsAsMeshes();
	Mesh* getHairStrangSpringsAsTriangleMeshes();
	Mesh* getHairStrandSpringsAsCurveMeshes();
	void updateHairStrandSpringMesh();
	void updateHairStrangSpringTriangleMesh();
	void updateHairStrandSpringCurveMesh();

	void setStiffness(f32 stiffness);
	void setDamping(f32 damping);
	void restart();
};