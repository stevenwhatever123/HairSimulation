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

void HairManager::generateHairStrandMassPoints()
{
	u32 currentMassPointSize = mass_points.size();

	// distance between two mass point
	f32 t = 0.1f;

	for (u32 i = 0; i < currentMassPointSize; i++)
	{
		vec3 old_position = mass_points[i]->getPosition();

		vec3 direction = mass_points[i]->getNormal();

		vec3 new_position = old_position + t * direction;

		vec2 texCoord = mass_points[i]->getTexCoord();

		MassPoint* new_mass_point = new MassPoint(new_position, direction, texCoord, 1.0f, false);

		// Link two mass point
		Spring* spring = new Spring(mass_points[i], new_mass_point, 0, 0, 0);

		mass_points.push_back(new_mass_point);
		springs.push_back(spring);
	}
}

std::vector<Mesh*> HairManager::getHairRootMassPointsAsMeshes()
{
	std::vector<Mesh*> mass_point_meshes;
	mass_point_meshes.resize(mass_points.size());

	for (u32 i = 0; i < mass_points.size(); i++)
	{
		mass_point_meshes[i] = new Mesh();

		mass_point_meshes[i]->name = "MassPointRoot" + i;

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

std::vector<Mesh*> HairManager::getHairStrandSpringsAsMeshes()
{
	std::vector<Mesh*> hair_springs_meshes;
	hair_springs_meshes.resize(springs.size());

	for (u32 i = 0; i < springs.size(); i++)
	{
		hair_springs_meshes[i] = new Mesh();

		hair_springs_meshes[i]->name = "MassPointSpring" + i;


		hair_springs_meshes[i]->positions.resize(2);
		//hair_springs_meshes[i]->positions.push_back
	}

	return hair_springs_meshes;
}