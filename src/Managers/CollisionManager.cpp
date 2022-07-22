#include "pch.h"
#include "Managers/CollisionManager.h"

CollisionManager::CollisionManager():
	aabbNodeRoots()
{

}

CollisionManager::~CollisionManager()
{

}

AABB* CollisionManager::generateAABB(std::vector<vec3>& positions)
{
	// Generate those first
	f32 xMin = positions[0].x;
	f32 xMax = positions[0].x;
	f32 yMin = positions[0].y;
	f32 yMax = positions[0].y;
	f32 zMin = positions[0].z;
	f32 zMax = positions[0].z;

	for (vec3& position : positions)
	{
		if (position.x < xMin)
			xMin = position.x;
		if (position.x > xMax)
			xMax = position.x;

		if (position.y < yMin)
			yMin = position.y;
		if (position.y > yMax)
			yMax = position.y;

		if (position.z < zMin)
			zMin = position.z;
		if (position.z > zMax)
			zMax = position.z;
	}

	AABB* aabb = new AABB(xMin, xMax, yMin, yMax, zMin, zMax);

	return aabb;
}

void CollisionManager::generateAABBTree(Mesh* mesh)
{
	AABB* aabb = generateAABB(mesh->positions);
	AABBNode* rootNode = new AABBNode(aabb);
	aabbNodeRoots.push_back(rootNode);

	bool divide_in_x_axis = true;
	recursiveAABBTreeGeneration(rootNode, mesh->positions, divide_in_x_axis, 3);
}

void CollisionManager::recursiveAABBTreeGeneration(AABBNode* node, std::vector<vec3>& positions,
	bool divide_in_x_axis, u32 count)
{
	// Base case
	if (count == 0)
		return;

	// Divide the AABB into half
	// based on the mid position of the mesh
	// i.e. the vec3 position

	vec3 sum(0);
	for (vec3 position : positions)
	{
		sum += position;
	}

	vec3 midPoint = sum * (1.0f / positions.size());

	{
		std::vector<vec3> lPosition;
		std::vector<vec3> rPosition;
		for (vec3& position : positions)
		{
			if (divide_in_x_axis)
			{
				if (position.x <= midPoint.x)
				{
					lPosition.push_back(position);
				}

				if (position.x >= midPoint.x)
				{
					rPosition.push_back(position);
				}
			}

			// Y axis
			if (!divide_in_x_axis)
			{
				if (position.y <= midPoint.y)
				{
					lPosition.push_back(position);
				}

				if (position.y >= midPoint.y)
				{
					rPosition.push_back(position);
				}
			}
		}

		AABB* laabb = generateAABB(lPosition);
		AABB* raabb = generateAABB(rPosition);

		AABBNode* lNode = new AABBNode(laabb);
		AABBNode* rNode = new AABBNode(raabb);

		node->addLeftNode(lNode);
		node->addRightNode(rNode);

		recursiveAABBTreeGeneration(node->getLeftNode(), lPosition, !divide_in_x_axis, count - 1);
		recursiveAABBTreeGeneration(node->getRightNode(), rPosition, !divide_in_x_axis, count - 1);
	}
}

void CollisionManager::update(std::vector<MassPoint*>& mass_points)
{
	//bool printed = false;

	//for (u32 i = 0; i < mass_points.size(); i++)
	//{
	//	for (AABBNode* node : aabbNodeRoots)
	//	{
	//		if (mass_points[i]->isHairRoot())
	//			continue;

	//		//if (node->getAABB()->checkIntersection(mass_points[i]->getPosition()))
	//		//{
	//		//	if (!printed)
	//		//	{
	//		//		printf("Collided\n");
	//		//		printed = true;
	//		//	}
	//		//}

	//		if (node->getAABB()->checkIntersection(mass_points[i]->getPosition()))
	//		{
	//			if (!printed)
	//			{
	//				printf("Collided\n");
	//				printed = true;
	//			}
	//		}
	//	}
	//}


}