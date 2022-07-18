#pragma once
#include "Types.h"

#include "Mesh.h"
#include "AABB.h"
#include "AABBNode.h"

#include "MassPoint.h"

class CollisionManager
{
private:

	std::vector<AABBNode*> aabbNodeRoots;

	void recursiveAABBTreeGeneration(AABBNode* node, std::vector<vec3>& positions, 
		bool divide_in_x_axis, u32 count);

public:

	AABB* generateAABB(std::vector<vec3>& positions);

	void generateAABBTree(Mesh* mesh);

public:
	CollisionManager();
	~CollisionManager();

	void update(std::vector<MassPoint*>& mass_points);
};