#pragma once
#include "Types.h"

#include <MassPoint.h>
#include <Spring.h>

class Strand
{
private:

public:

	std::vector<Spring*> springs;

	std::vector<Spring*> bending_springs;
	std::vector<Spring*> torsion_springs;

public:

	Strand();
	~Strand();

	void create_bending_springs(f32 stiffness, f32 damping);
	void create_torsion_springs(f32 stiffness, f32 damping);

	void update(f32 dt);
	void update_bending(f32 dt);
	void update_torsion(f32 dt);
	void updateImproved(f32 dt);
};

