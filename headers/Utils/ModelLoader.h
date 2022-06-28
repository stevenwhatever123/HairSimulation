#pragma once
#include "Types.h"

#include "Mesh.h"
#include "Material.h"
#include "Model.h"

namespace SystemUtils
{
	Model* readModel(const char* filename);
	Model* extractScene(const aiScene* pScene);
}
