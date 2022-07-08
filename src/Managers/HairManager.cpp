#include "pch.h"
#include "Managers/HairManager.h"

HairManager::HairManager():
	mass_points(),
	hair_springs_meshes(nullptr)
{

}

HairManager::~HairManager()
{

}

void HairManager::update(float dt)
{
	for (Spring* spring : springs)
	{
		spring->getMassPointOne()->resetSpringForce();
		spring->getMassPointTwo()->resetSpringForce();
	}

	for (Spring* spring : springs)
	{
		spring->update(dt);

		spring->getMassPointOne()->addSpringForce(spring->getP1TotalForce());
		spring->getMassPointTwo()->addSpringForce(spring->getP2TotalForce());
	}

	for (MassPoint* mp : mass_points)
	{
		if (mp->isHairRoot())
			continue;

		mp->update(dt);
	}
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

		MassPoint* mass_point = new MassPoint(v, n, tc, 0.1f, true);

		mass_points.push_back(mass_point);
	}

	printf("Generated %i hair root mass points\n", mass_points.size());
}

void HairManager::generateHairStrandMassPoints(u32 mass_point_per_strand)
{
	u32 currentMassPointSize = mass_points.size();

	// distance between two mass point
	//f32 t = 0.001f;
	f32 t = 0.2f;

	float stiffness = 100.0f;
	float damping = 2.0f;

	for (u32 i = 0; i < currentMassPointSize; i++)
	{
		vec3 old_position = mass_points[i]->getPosition();

		vec3 direction = mass_points[i]->getNormal();

		vec3 new_position = old_position + t * direction;

		vec2 texCoord = mass_points[i]->getTexCoord();

		f32 old_mass = mass_points[i]->getMass();

		MassPoint* old_mass_point = mass_points[i];

		MassPoint* new_mass_point = new MassPoint(new_position, direction, texCoord, old_mass, false);

		Spring* spring = new Spring(old_mass_point, new_mass_point, stiffness, damping);

		mass_points.push_back(new_mass_point);
		springs.push_back(spring);

		for (u32 j = 1; j < mass_point_per_strand; j++)
		{
			old_position = new_position;
			new_position = old_position + t * direction;
			
			old_mass_point = new_mass_point;

			new_mass_point = new MassPoint(new_position, direction, texCoord, old_mass, false);

			Spring* spring = new Spring(old_mass_point, new_mass_point, stiffness, damping);

			mass_points.push_back(new_mass_point);
			springs.push_back(spring);
		}
	}

	printf("Generated %i hair root mass points\n", mass_points.size());
}

Mesh* HairManager::getHairStrandSpringsAsMeshes()
{
	hair_springs_meshes = new Mesh();

	hair_springs_meshes->name = "MassPointSpring";
	hair_springs_meshes->positions.resize(springs.size() * 2);
	hair_springs_meshes->normals.resize(springs.size() * 2);
	hair_springs_meshes->texCoords.resize(springs.size() * 2);
	hair_springs_meshes->indicies.resize(springs.size() * 2);

	for (u32 i = 0; i < springs.size(); i++)
	{
		hair_springs_meshes->positions[i * 2] = springs[i]->getMassPointOne()->getPosition();
		hair_springs_meshes->positions[i * 2 + 1] = springs[i]->getMassPointTwo()->getPosition();

		hair_springs_meshes->normals[i * 2] = springs[i]->getMassPointOne()->getNormal();
		hair_springs_meshes->normals[i * 2 + 1] = springs[i]->getMassPointTwo()->getNormal();

		hair_springs_meshes->texCoords[i * 2] = springs[i]->getMassPointOne()->getTexCoord();
		hair_springs_meshes->texCoords[i * 2 + 1] = springs[i]->getMassPointTwo()->getTexCoord();

		hair_springs_meshes->indicies[i * 2] = i * 2;
		hair_springs_meshes->indicies[i * 2 + 1] = i * 2 + 1;

		hair_springs_meshes->isMesh = false;
		hair_springs_meshes->isMassPoint = true;
		hair_springs_meshes->primitive_type = GL_LINES;
	}

	return hair_springs_meshes;
}

void HairManager::updateHairStrandSpringMesh()
{
	if (hair_springs_meshes == nullptr)
		return;

	for (u32 i = 0; i < springs.size(); i++)
	{
		hair_springs_meshes->positions[i * 2] = springs[i]->getMassPointOne()->getPosition();
		hair_springs_meshes->positions[i * 2 + 1] = springs[i]->getMassPointTwo()->getPosition();

		hair_springs_meshes->normals[i * 2] = springs[i]->getMassPointOne()->getNormal();
		hair_springs_meshes->normals[i * 2 + 1] = springs[i]->getMassPointTwo()->getNormal();

		hair_springs_meshes->texCoords[i * 2] = springs[i]->getMassPointOne()->getTexCoord();
		hair_springs_meshes->texCoords[i * 2 + 1] = springs[i]->getMassPointTwo()->getTexCoord();

		hair_springs_meshes->indicies[i * 2] = i * 2;
		hair_springs_meshes->indicies[i * 2 + 1] = i * 2 + 1;
	}

	hair_springs_meshes->updateBuffers();
}