#pragma once
#include "Mesh.h"
#include "Material.h"

class Model
{
public:
	std::vector<Mesh*> meshes;
	std::vector<Material*> materials;

public:
	Model();
	~Model();
};

