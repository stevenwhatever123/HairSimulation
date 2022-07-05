#include "pch.h"
#include "Managers/HairManager.h"

HairManager::HairManager():
	hairRootPositions(),
	hairRootNormals(),
	hairRootTexCoords(),
	hairRootIndicies()
{

}

HairManager::~HairManager()
{

}

void HairManager::generateHairRoots(const Mesh *mesh)
{
	int currentIndiciesSize = hairRootIndicies.size();

	//if (mesh->positions.size() > 500)
	//	return;

	for (u32 i = 0; i < mesh->indicies.size() - 3; i+=3)
	{
		// Get the middle point of the face
		vec3 v0 = mesh->positions[mesh->indicies[i + 0]];
		vec3 v1 = mesh->positions[mesh->indicies[i + 1]];
		vec3 v2 = mesh->positions[mesh->indicies[i + 2]];

		vec3 n0 = mesh->normals[mesh->indicies[i + 0]];
		vec3 n1 = mesh->normals[mesh->indicies[i + 1]];
		vec3 n2 = mesh->normals[mesh->indicies[i + 2]];

		vec2 t0 = mesh->texCoords[mesh->indicies[i + 0]];
		vec2 t1 = mesh->texCoords[mesh->indicies[i + 1]];
		vec2 t2 = mesh->texCoords[mesh->indicies[i + 2]];

		vec3 v = (v0 + v1 + v2) / 3.0f;

		vec3 n = (n0 + n1 + n2) / 3.0f;

		vec2 tc = (t0 + t1 + t2) / 3.0f;

		hairRootPositions.push_back(v);
		hairRootNormals.push_back(n);
		hairRootTexCoords.push_back(tc);
		//hairRootIndicies.push_back((i / 3.0f));
		hairRootIndicies.push_back(currentIndiciesSize + (i / 3.0f));
	}

	printf("Generated %i hair roots\n", hairRootPositions.size());
}

Mesh* HairManager::getHairRootAsMeshes()
{
	Mesh* mesh = new Mesh();
	mesh->name = "HairRootMesh";
	mesh->positions.resize(hairRootPositions.size());
	mesh->normals.resize(hairRootNormals.size());
	mesh->texCoords.resize(hairRootTexCoords.size());
	mesh->indicies.resize(hairRootIndicies.size());

	for (u32 i = 0; i < hairRootPositions.size(); i++)
	{
		mesh->positions[i] = hairRootPositions[i];
		mesh->normals[i] = hairRootNormals[i];
		mesh->texCoords[i] = hairRootTexCoords[i];
		mesh->indicies[i] = hairRootIndicies[i];
	}

	mesh->isHairRoot = true;
	mesh->isMesh = false;
	mesh->primitive_type = GL_POINTS;

	return mesh;
}