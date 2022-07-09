#include "pch.h"
#include "Renderer.h"
#include "GLShader.h"

Renderer::Renderer(int width, int height, Camera* camera) :
	width(width),
	height(height),
	camera(camera),
	UBO(-1),
	shaderPrograms(),
	projectionMatrix(1),
	clear_color(0),
	rendObjects(),
	mass_point_count(0)
{
	init();
	genGLBuffers();
}

Renderer::~Renderer()
{

}

void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glEnable(GL_PROGRAM_POINT_SIZE);

	//glDepthFunc(GL_LESS);
	glDepthFunc(GL_LEQUAL);

	set_clear_color(vec4(0.4f, 0.4f, 0.4f, 1));

	// Set projection matrix
	projectionMatrix = glm::perspective(
		glm::radians(90.0f),
		4.0f/ 3.0f,
		0.1f,
		1000.0f
	);
}

void Renderer::setFramebufferSize(int width, int height)
{
	if (this->width == width && this->height == height)
		return;

	if (width < 1 || height < 1)
		return;

	this->width = width;
	this->height = height;

	printf("Framebuffer Width: %i\n", this->width);
	printf("Framebuffer Height: %i\n", this->height);

	glViewport(0, 0, width, height);

	// Update projection matrix
	projectionMatrix = glm::perspective(
		glm::radians(90.0f),
		(f32)width / (f32)height,
		0.1f,
		100.0f
	);
}

void Renderer::addShaderPrograms(const std::vector<GLShader*>& shaderPrograms)
{
	for (GLShader* program : shaderPrograms)
	{
		this->shaderPrograms.emplace_back(program);
	}
}

void Renderer::draw()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLShader* shaderProgram;

	for (RendObj &rendObj : rendObjects)
	{
		shaderProgram = shaderPrograms[rendObj.shaderIndex];

		glBindVertexArray(rendObj.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, rendObj.VBO);
		GLuint posAttri = shaderProgram->getAttribLocation("position");
		glVertexAttribPointer(
			posAttri,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, rendObj.NBO);
		GLuint normalAttri = shaderProgram->getAttribLocation("normal");
		glVertexAttribPointer(
			normalAttri,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ARRAY_BUFFER, rendObj.TCBO);
		GLuint texCoordAttri = shaderProgram->getAttribLocation("texCoord");
		glVertexAttribPointer(
			texCoordAttri,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendObj.EBO);

		shaderProgram->use();

		shaderProgram->setUniformMat4("viewMatrix", camera->getTransformation());
		shaderProgram->setUniformMat4("projectionMatrix", projectionMatrix);
		shaderProgram->setUniformMat4("modelMatrix", rendObj.getTransformation());

		if (rendObj.materialIndex > 0)
		{
			shaderProgram->setUniformMaterial(UBO, rendMaterials[rendObj.materialIndex]);

			glBindTexture(GL_TEXTURE_2D, materials[rendObj.materialIndex].texture_id);
		}

		glDrawElements(
			rendObj.primitive,
			rendObj.elementSize,
			GL_UNSIGNED_INT,
			(void*) 0
		);
	}
}

void Renderer::genGLBuffers()
{
	// Uniform buffer
	glGenBuffers(1, &UBO);

	// Allocate memory for uniform buffer
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 32, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, sizeof(MaterialUniform));
}

void Renderer::addMesh(Mesh* mesh)
{
	RendObj rendObj{};
	rendObj.translation = mat4(1);
	rendObj.rotation = mat4(1);
	rendObj.scaling = mat4(1);

	rendObj.shaderIndex = mesh->shaderIndex;
	rendObj.primitive = mesh->primitive_type;
	rendObj.elementSize = mesh->indicies.size();
	rendObj.VBO = mesh->VBO;
	rendObj.NBO = mesh->NBO;
	rendObj.TCBO = mesh->TCBO;
	rendObj.EBO = mesh->EBO;
	rendObj.VAO = mesh->VAO;

	//u32 currentMaterialSize = materials.size();
	//rendObj.materialIndex = currentMaterialSize + mesh->material_index;
	rendObj.materialIndex = mesh->material_index;

	rendObjects.push_back(rendObj);
}

void Renderer::addMaterial(Material* material)
{
	MaterialUniform rendMaterial = material->getMaterialUniform();

	if (material->has_texture)
	{
		// Upload texture to gpu
		glGenTextures(1, &material->texture_id);
		glBindTexture(GL_TEXTURE_2D, material->texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, material->width, material->height, 0, 
			(material->numChannels == 3) ? GL_RGB: GL_RGBA, GL_UNSIGNED_BYTE, 
			material->texture_image->data);
		glGenerateMipmap(GL_TEXTURE_2D);

		material->freeTextureImage();
	}

	rendMaterials.push_back(rendMaterial);
	materials.push_back(*material);
}

void Renderer::addMeshScene(Model* meshScene)
{
	for (Mesh* mesh : meshScene->meshes)
	{
		mesh->generateBuffers(shaderPrograms[0], 0);
		addMesh(mesh);
	}

	for (Material* material : meshScene->materials)
	{
		addMaterial(material);
	}
}

void Renderer::set_clear_color(vec4 color)
{
	clear_color.x = color.x;	// R
	clear_color.y = color.y;	// G
	clear_color.z = color.z;	// B
	clear_color.w = color.w;	// A

	glClearColor(
		clear_color.x,
		clear_color.y,
		clear_color.z,
		clear_color.w
	);
}

void Renderer::set_rendObj_rotation(u32 index, vec3 rotation)
{
	rendObjects[index].rotation =
		glm::eulerAngleXYZ(rotation.y * 0.005f, rotation.x * 0.005f, rotation.z * 0.005f);
}

void Renderer::set_rendMassPoint_rotation(u32 index, vec3 rotation)
{
	rendObjects[index].rotation =
		glm::eulerAngleXYZ(rotation.y * 0.005f, rotation.x * 0.005f, rotation.z * 0.005f);
}

void Renderer::set_all_rendable_rotation(vec3 rotation)
{
	for (u32 i = 0; i < rendObjects.size(); i++)
		set_rendObj_rotation(i, rotation);

	for (u32 i = 0; i < rendObjects.size(); i++)
		set_rendMassPoint_rotation(i, rotation);
}

Camera* Renderer::getCamera()
{
	return camera;
}