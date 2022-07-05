#include "pch.h"
#include "Utils/ModelLoader.h"

Model* SystemUtils::readModel(const char* filename)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename,
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_GenSmoothNormals |
		aiProcess_JoinIdenticalVertices);

	if (pScene)
	{
		return extractScene(pScene);
	}
	else
	{
		return nullptr;
	}
}

Model* SystemUtils::extractScene(const aiScene* pScene)
{
	const aiVector3D zero3D(0);

	Model *meshScene = new Model;

	meshScene->meshes.resize(pScene->mNumMeshes);

	// Get position, normal and texture coordinates
	for (u32 i = 0; i < pScene->mNumMeshes; i++)
	{
		const aiMesh* pMesh = pScene->mMeshes[i];

		Mesh* mesh = new Mesh();

		mesh->name = pMesh->mName.C_Str();

		mesh->positions.resize(pMesh->mNumVertices);
		mesh->normals.resize(pMesh->mNumVertices);
		mesh->texCoords.resize(pMesh->mNumVertices);

		const bool has_texture = pMesh->HasTextureCoords(0);

		const aiVector3D* pVertex = pMesh->mVertices;
		const aiVector3D* pNormal = pMesh->mNormals;
		const aiVector3D* pTexCoords = has_texture? pMesh->mTextureCoords[0] : &zero3D;

		for (u32 j = 0; j < pMesh->mNumVertices; j++)
		{
			mesh->positions[j].x = (f32)pVertex->x;
			mesh->positions[j].y = (f32)pVertex->y;
			mesh->positions[j].z = (f32)pVertex->z;

			mesh->normals[j].x = (f32)pNormal->x;
			mesh->normals[j].y = (f32)pNormal->y;
			mesh->normals[j].z = (f32)pNormal->z;

			mesh->texCoords[j].x = (f32)pTexCoords->x;
			mesh->texCoords[j].y = (f32)pTexCoords->y;

			pVertex++;
			pNormal++;
			has_texture ? pTexCoords++ : NULL;
		}

		const aiFace* face = pMesh->mFaces;
		for (u32 j = 0; j < pMesh->mNumFaces; j++)
		{
			for (u32 k = 0; k < face->mNumIndices; k++)
			{
				mesh->indicies.push_back((u32)face->mIndices[k]);
			}

			face++;
		}

		//mesh->primitive_type = pMesh->mPrimitiveTypes;
		mesh->primitive_type = GL_TRIANGLES;
		mesh->material_index = pMesh->mMaterialIndex;

		meshScene->meshes[i] = mesh;
	}

	// Extract material data if available
	if (pScene->HasMaterials())
	{
		meshScene->materials.resize(pScene->mNumMaterials);

		for (u32 i = 0; i < pScene->mNumMaterials; i++)
		{
			Material* material = new Material();

			aiMaterial* pMaterial = pScene->mMaterials[i];

			// Materials?
			aiString materialName;
			aiReturn ret;

			ret = pMaterial->Get(AI_MATKEY_NAME, materialName);
			if (ret != AI_SUCCESS) materialName = "";

			material->name = materialName.C_Str();

			int numTextures = pMaterial->GetTextureCount(aiTextureType_DIFFUSE);
			aiString textureName;
			if (numTextures > 0)
			{
				ret = pMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), 
					textureName);

				material->has_texture = true;
				material->texture_name = textureName.C_Str();
			}

			// Color
			aiColor3D color(0, 0, 0);
			ret = pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);

			material->color.x = color.r;
			material->color.y = color.g;
			material->color.z = color.b;
			material->color.w = 1.0f;

			if (material->has_texture)
			{
				// Texture
				loadTexture(material);
			}

			meshScene->materials[i] = material;
		}

		// Find which mesh is a skull for hair generation
		for (Mesh* mesh : meshScene->meshes)
		{
			if (meshScene->materials[mesh->material_index]->name.find("skull")
				!= std::string::npos)
			{
				mesh->isSkull = true;
			}
			mesh->isMesh = true;
		}
	}

	return meshScene;
}

void SystemUtils::loadTexture(Material* pMaterial)
{
	Image* image = new Image();
	image->readImage(pMaterial->texture_name.c_str(),
		pMaterial->width, pMaterial->height, pMaterial->numChannels);

	pMaterial->setTextureImage(image);
}