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

	f64 time_step = 0.0001f;

	f64 accumulator = 0.0f;

public:

	i32 numMassPointPerStrand = 8;

	// This works great with normal string
	//f32 stiffness = 4.0f;
	//f32 damping = 0.07f;

	//================================
	// This works great with curly hair

	//f32 stiffness = 4.0f;
	//f32 damping = 0.3f;

	//f32 bending_stiffness = 0.5f;
	//f32 bending_damping = 0.001f;

	//f32 torsion_stiffness = 0.5f;
	//f32 torsion_damping = 0.001f;

	//================================

	f32 stiffness = 4.0f;
	f32 damping = 0.3f;

	f32 bending_stiffness = 0.5f;
	f32 bending_damping = 0.1f;

	f32 torsion_stiffness = 0.5f;
	f32 torsion_damping = 0.1f;

	// Works great with normal mp
	//f32 stiffness = 2.0f;
	//f32 damping = 0.01f;

	f32 longStrandLength = 1.4f;
	f32 shortStrandLength = 0.8f;

	f32 mass = 0.004f;

	//f32 stiffness = 5.0f;
	//f32 damping = 0.2f;

	std::vector<MassPoint*> mass_points;
	std::vector<Spring*> springs;
	std::vector<Strand*> strands;
	

public:
	HairManager();
	~HairManager();

	void update(f64 dt);

	void generateHairRootMassPoints(const Mesh* mesh);

	void generateHairStrandMassPoints(u32 mass_point_per_strand);

	void generateSingleHairStrand();

	Mesh* getHairStrandSpringsAsMeshes();
	Mesh* getHairStrandMassPointsAsMeshes();
	Mesh* getHairStrandSpringsAsCurveMeshes();
	void updateHairStrandSpringMesh();
	void updateHairStrandMassPointMesh();
	void updateHairStrandSpringCurveMesh();

	void setStiffness(f32 stiffness);
	void setDamping(f32 damping);
	void restart();
};