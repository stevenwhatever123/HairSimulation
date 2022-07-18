#pragma once
#include "Types.h"

#include "AABB.h"

class AABBNode
{
private:

	AABB* aabb;

	AABBNode* lNode;
	AABBNode* rNode;

public:

public:

	AABBNode();
	AABBNode(AABB* aabb);
	AABBNode(AABB* aabb, AABBNode* lNode, AABBNode* rNode);
	~AABBNode();

	void addLeftNode(AABBNode* node);
	void addRightNode(AABBNode* node);

	AABB* getAABB();

	AABBNode* getLeftNode();
	AABBNode* getRightNode();

	bool checkTreeIntersection(vec3& position);
};