#include "pch.h"
#include "Managers/HairManager.h"

HairManager::HairManager():
	mass_points()
{

}

HairManager::~HairManager()
{

}

void HairManager::generateHairRootMassPoints(const Mesh *mesh)
{
	for (u32 i = 0; i < mesh->indicies.size() - 3; i += 3)
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

		MassPoint* mass_point = new MassPoint(v, n, tc, 1.0f, true);

		mass_points.push_back(mass_point);
	}

	printf("Generated %i hair root mass points\n", mass_points.size());
}

std::vector<Mesh*> HairManager::getHairRootMassPointsAsMeshes()
{
	std::vector<Mesh*> mass_point_meshes;
	mass_point_meshes.resize(mass_points.size());

	for (u32 i = 0; i < mass_points.size(); i++)
	{
		mass_point_meshes[i] = new Mesh();

		mass_point_meshes[i]->name = "MassPointRoot";

		mass_point_meshes[i]->positions.push_back(mass_points[i]->getPosition());
		mass_point_meshes[i]->normals.push_back(mass_points[i]->getNormal());
		mass_point_meshes[i]->texCoords.push_back(mass_points[i]->getTexCoord());
		// Because there is only one point
		mass_point_meshes[i]->indicies.push_back(0);

		mass_point_meshes[i]->isMesh = false;
		mass_point_meshes[i]->isMassPoint = true;
		mass_point_meshes[i]->primitive_type = GL_POINTS;
		mass_point_meshes[i]->mass_point_id = i;
	}

	return mass_point_meshes;
}