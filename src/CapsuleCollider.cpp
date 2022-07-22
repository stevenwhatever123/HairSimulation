#include "pch.h"
#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider():
	tip(0),
	base(0),
	radius(0),
	tipSphereCenter(0),
	baseSphereCenter(0),
	normal(0),
	lineEndOffset(0),
	transformation(1)
{

}

CapsuleCollider::CapsuleCollider(vec3 tip, vec3 base, f32 radius):
	tip(tip),
	base(base),
	radius(radius),
	transformation(1)
{
	normal = glm::normalize(tip - base);
	lineEndOffset = normal * radius;
	tipSphereCenter = tip + lineEndOffset;
	baseSphereCenter = base + lineEndOffset;
}

CapsuleCollider::~CapsuleCollider()
{

}

void CapsuleCollider::printInformation()
{
	printf("Tip: %s\n", glm::to_string(tip).c_str());
	printf("Base: %s\n", glm::to_string(base).c_str());
	printf("Tip Sphere Center: %s\n", glm::to_string(tipSphereCenter).c_str());
	printf("Base Sphere Center: %s\n", glm::to_string(baseSphereCenter).c_str());
	printf("Radius: %f\n", radius);
	printf("Line end offset: %s\n", glm::to_string(lineEndOffset).c_str());
}

void CapsuleCollider::updatePositionByTransformation()
{
	tip = vec3(transformation * vec4(tip, 1.0f));
	base = vec3(transformation* vec4(base, 1.0f));

	normal = glm::normalize(tip - base);
	lineEndOffset = normal * radius;
	tipSphereCenter = tip + lineEndOffset;
	baseSphereCenter = base + lineEndOffset;
}

void CapsuleCollider::update()
{

}