#include "pch.h"
#include "AABBNode.h"

AABBNode::AABBNode() :
	aabb(nullptr),
	lNode(nullptr),
	rNode(nullptr)
{

}

AABBNode::AABBNode(AABB* aabb):
	aabb(aabb),
	lNode(nullptr),
	rNode(nullptr)
{

}

AABBNode::AABBNode(AABB* aabb, AABBNode* lNode, AABBNode* rNode):
	aabb(aabb),
	lNode(lNode),
	rNode(rNode)
{

}

AABBNode::~AABBNode()
{

}

void AABBNode::addLeftNode(AABBNode* node)
{
	lNode = node;
}

void AABBNode::addRightNode(AABBNode* node)
{
	rNode = node;
}

AABB* AABBNode::getAABB()
{
	return this->aabb;
}

AABBNode* AABBNode::getLeftNode()
{
	return this->lNode;
}

AABBNode* AABBNode::getRightNode()
{
	return this->rNode;
}

bool AABBNode::checkTreeIntersection(vec3& position)
{
	return false;
}