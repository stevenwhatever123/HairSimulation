#include "pch.h"
#include "Utils/ModelLoader.h"

Model* SystemUtils::readModel(const char* filename)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename,
		aiProcess_Triangulate |
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

		mesh->positions.resize(pMesh->mNumVertices);
		mesh->normals.resize(pMesh->mNumVertices);
		mesh->texCoords.resize(pMesh->mNumVertices);
		mesh->face.resize(pMesh->mNumFaces);

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
			mesh->face[j].resize(face->mNumIndices);

			for (u32 k = 0; k < face->mNumIndices; k++)
			{
				mesh->face[j][k] = (u32)face->mIndices[k];
			}

			face++;
		}

		mesh->primitive_type = pMesh->mPrimitiveTypes;

		const bool has_color = pMesh->HasVertexColors(0);

		mesh->has_color = has_color;

		if (has_color)
		{
			mesh->color.x = (f32)pMesh->mColors[0]->r;
			mesh->color.y = (f32)pMesh->mColors[0]->g;
			mesh->color.z = (f32)pMesh->mColors[0]->b;
			mesh->color.w = (f32)pMesh->mColors[0]->a;
		}

		meshScene->meshes[i] = mesh;
	}

	// Extract material data if available
	if (pScene->HasMaterials())
	{
		std::cout << "I have material" << "\n";
		for (u32 i = 0; i < pScene->mNumMaterials; i++)
		{
			aiMaterial* pMaterial = pScene->mMaterials[0];

			// Materials?
			//mesh->material_index = pMesh->mMaterialIndex;
		}
	}

	return meshScene;
}