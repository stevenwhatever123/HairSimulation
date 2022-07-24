#include "pch.h"
#include "Managers/CollisionManager.h"

CollisionManager::CollisionManager():
	detect(false),
	aabbNodeRoots(),
	capsuleColliders()
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

void CollisionManager::generatePresetCapsuleCollider()
{
	// Y-Axis
	CapsuleCollider* capsuleHor = new CapsuleCollider(
		vec3(0.0007734895f, 1.670403f, -0.016873f), 0.8f, 3.298687f, vec3(0, 1, 0));

	capsuleColliders.push_back(capsuleHor);

	// X-Axis
	CapsuleCollider* capsuleVer = new CapsuleCollider(
		vec3(0.0007734895f, 0.27f, -0.45f), 0.6f, 3.298687f, vec3(1, 0, 0));

	capsuleColliders.push_back(capsuleVer);

	// Back of the head
	CapsuleCollider* capsuleBack = new CapsuleCollider(
		vec3(0.0007734895f, 2.4f, -0.49f), 0.7f, 1.5f, vec3(0, 1, 0));

	capsuleColliders.push_back(capsuleBack);

	// Face
	CapsuleCollider* capsuleFace = new CapsuleCollider(
		vec3(0.0007734895f, 2.26f, 0.24f), 0.8f, 1.0f, vec3(0, 1, 0));

	capsuleColliders.push_back(capsuleFace);
}

void CollisionManager::generateCapsuleCollider(Mesh* mesh)
{
	vec3 meshCenterPoint(0);
	for (vec3& position : mesh->positions)
	{
		meshCenterPoint += position;
	}
	meshCenterPoint = meshCenterPoint * (1.0f / mesh->positions.size());

	CapsuleCollider* capsule = new CapsuleCollider(meshCenterPoint, 1.0f, 2.0f, vec3(0, 1, 0));
	capsuleColliders.push_back(capsule);
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

void CollisionManager::detectCollision()
{
	detect = true;
}

void CollisionManager::undetectCollision()
{
	detect = false;
}

void CollisionManager::update(std::vector<MassPoint*>& mass_points)
{
	if (!detect)
		return;


	for (CapsuleCollider* collider : capsuleColliders)
	{
		//collider->printInformation();
		for (MassPoint* mp : mass_points)
			collider->checkCollision(mp);
	}
}