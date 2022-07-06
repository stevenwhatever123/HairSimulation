#include "pch.h"

#include "Model.h"

Model::Model():
	meshes(),
	materials()
{

}

Model::~Model()
{

}

vec3 Model::getCenterPosition()
{
	vec3 center(0);
	f32 totalPosition = 0;

	for (Mesh* mesh : meshes)
	{
		for (vec3 position : mesh->positions)
		{
			center += position;
			totalPosition++;
		}
	}

	return center / totalPosition;
}
