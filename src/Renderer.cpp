#include "pch.h"
#include "Renderer.h"
#include "GLShader.h"

Renderer::Renderer(int width, int height, Camera* camera) :
	width(width),
	height(height),
	camera(camera),
	VBO(-1),
	NBO(-1),
	TCBO(-1),
	EBO(-1),
	UBO(-1),
	VAO(-1),
	shaderPrograms(),
	projectionMatrix(1),
	clear_color(0),
	positions(),
	normals(),
	texCoords(),
	indicies(),
	rendObjs(),
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

	glBindVertexArray(VAO);

	for (RendObj &renderObject : rendObjs)
	{
		if (renderObject.isMesh)
		{
			glDisable(GL_PROGRAM_POINT_SIZE);
			shaderProgram = shaderPrograms[0];

			shaderProgram->use();

			shaderProgram->setUniformMat4("viewMatrix", camera->getTransformation());
			shaderProgram->setUniformMat4("projectionMatrix", projectionMatrix);

			shaderProgram->setUniformMat4("modelMatrix", renderObject.getTransformation());

			shaderProgram->setUniformMaterial(UBO, rendMaterials[renderObject.material_index]);

			glBindTexture(GL_TEXTURE_2D, materials[renderObject.material_index].texture_id);

			glDrawElements(
				renderObject.primitive,
				renderObject.endIndex - renderObject.startIndex,
				GL_UNSIGNED_INT,
				(void*)(renderObject.startIndex * sizeof(u32)));

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	for (RendMassPoint& renderMassPoint : rendMassPoints)
	{
		glEnable(GL_PROGRAM_POINT_SIZE);
		shaderProgram = shaderPrograms[1];

		shaderProgram->use();

		//shaderProgram->setUniformVec3("u_position", renderMassPoint.position);

		shaderProgram->setUniformMat4("viewMatrix", camera->getTransformation());
		shaderProgram->setUniformMat4("projectionMatrix", projectionMatrix);
		shaderProgram->setUniformMat4("modelMatrix", renderMassPoint.getTransformation());

		glDrawElements(
			renderMassPoint.primitive,
			renderMassPoint.endIndex - renderMassPoint.startIndex,
			GL_UNSIGNED_INT,
			(void*)(renderMassPoint.startIndex * sizeof(u32)));
	}
}

void Renderer::genGLBuffers()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &NBO);
	glGenBuffers(1, &TCBO);
	glGenBuffers(1, &EBO);

	glGenBuffers(1, &UBO);

	// Allocate memory for uniform buffer
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 32, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, sizeof(MaterialUniform));

	glGenVertexArrays(1, &VAO);
}

void Renderer::addObject(Mesh* mesh)
{
	RendObj renderObject{};
	renderObject.translation = mat4(1);
	renderObject.rotation = mat4(1);
	renderObject.scaling = mat4(1);
	renderObject.startIndex = indicies.size();
	renderObject.primitive = mesh->primitive_type;
	renderObject.isMesh = mesh->isMesh;
	renderObject.isMassPoint = mesh->isMassPoint;

	const u32 currentMaterialSize = rendMaterials.size();
	renderObject.material_index = currentMaterialSize + mesh->material_index;

	const u32 currentVerticesSize = positions.size();

	// Copy vertex position from mesh to the renderer
	copy(mesh->positions.begin(), mesh->positions.end(), std::back_inserter(positions));
	// Copy vertex normal from mesh to the renderer
	copy(mesh->normals.begin(), mesh->normals.end(), std::back_inserter(normals));
	// Copy texture coordinates from mesh to the renderer
	copy(mesh->texCoords.begin(), mesh->texCoords.end(), std::back_inserter(texCoords));

	// Copy indicies
	for (u32 i = 0; i < mesh->indicies.size(); i++)
	{
		indicies.push_back(currentVerticesSize + mesh->indicies[i]);
	}

	renderObject.endIndex = indicies.size();

	rendObjs.push_back(renderObject);

	// Position Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		positions.size() * sizeof(vec3),
		positions.data(),
		GL_STATIC_DRAW);

	GLShader* shaderProgram = shaderPrograms[0];

	// Positions Attributions
	GLuint positionAttri = shaderProgram->getAttribLocation("position");
	glVertexAttribPointer(
		positionAttri,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexArrayAttrib(VAO, positionAttri);

	// Normal Buffer
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER,
		normals.size() * sizeof(vec3),
		normals.data(),
		GL_STATIC_DRAW);

	// Normal Attributions
	GLuint normalAttri = shaderProgram->getAttribLocation("normal");
	glVertexAttribPointer(
		normalAttri,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexArrayAttrib(VAO, normalAttri);

	// Texture Coordinate Buffer
	glBindBuffer(GL_ARRAY_BUFFER, TCBO);
	glBufferData(GL_ARRAY_BUFFER,
		texCoords.size() * sizeof(vec2),
		texCoords.data(),
		GL_STATIC_DRAW);

	// Texture Coordinates Attributions
	GLuint texCoordAttri = shaderProgram->getAttribLocation("texCoord");
	glVertexAttribPointer(
		texCoordAttri,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexArrayAttrib(VAO, texCoordAttri);
	
	// Element / Indicies Array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indicies.size() * sizeof(u32),
		indicies.data(),
		GL_STATIC_DRAW
	);
}

void Renderer::addMassPoint(Mesh* mesh)
{
	RendMassPoint renderObject{};
	renderObject.translation = mat4(1);
	renderObject.rotation = mat4(1);
	renderObject.scaling = mat4(1);
	renderObject.startIndex = indicies.size();
	renderObject.primitive = mesh->primitive_type;
	renderObject.isMesh = mesh->isMesh;
	renderObject.isMassPoint = mesh->isMassPoint;
	// Mass point has only one position
	renderObject.position = mesh->positions[0];

	if (renderObject.isMassPoint)
	{
		renderObject.mass_point_id = mass_point_count;
		mass_point_count++;
	}

	const u32 currentMaterialSize = rendMaterials.size();
	renderObject.material_index = currentMaterialSize + mesh->material_index;

	const u32 currentVerticesSize = positions.size();

	// Copy vertex position from mesh to the renderer
	copy(mesh->positions.begin(), mesh->positions.end(), std::back_inserter(positions));
	// Copy vertex normal from mesh to the renderer
	copy(mesh->normals.begin(), mesh->normals.end(), std::back_inserter(normals));
	// Copy texture coordinates from mesh to the renderer
	copy(mesh->texCoords.begin(), mesh->texCoords.end(), std::back_inserter(texCoords));

	// Copy indicies
	for (u32 i = 0; i < mesh->indicies.size(); i++)
	{
		indicies.push_back(currentVerticesSize + mesh->indicies[i]);
	}

	renderObject.endIndex = indicies.size();

	rendMassPoints.push_back(renderObject);

	// Position Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		positions.size() * sizeof(vec3),
		positions.data(),
		GL_STATIC_DRAW);

	GLShader* shaderProgram = shaderPrograms[0];

	// Positions Attributions
	GLuint positionAttri = shaderProgram->getAttribLocation("position");
	glVertexAttribPointer(
		positionAttri,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexArrayAttrib(VAO, positionAttri);

	// Normal Buffer
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER,
		normals.size() * sizeof(vec3),
		normals.data(),
		GL_STATIC_DRAW);

	// Normal Attributions
	GLuint normalAttri = shaderProgram->getAttribLocation("normal");
	glVertexAttribPointer(
		normalAttri,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexArrayAttrib(VAO, normalAttri);

	// Texture Coordinate Buffer
	glBindBuffer(GL_ARRAY_BUFFER, TCBO);
	glBufferData(GL_ARRAY_BUFFER,
		texCoords.size() * sizeof(vec2),
		texCoords.data(),
		GL_STATIC_DRAW);

	// Texture Coordinates Attributions
	GLuint texCoordAttri = shaderProgram->getAttribLocation("texCoord");
	glVertexAttribPointer(
		texCoordAttri,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexArrayAttrib(VAO, texCoordAttri);

	// Element / Indicies Array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indicies.size() * sizeof(u32),
		indicies.data(),
		GL_STATIC_DRAW
	);
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
		addObject(mesh);
	}

	for (Material* material : meshScene->materials)
	{
		addMaterial(material);
	}

	// Clear mesh data from cpu
	positions.clear();
	normals.clear();
	texCoords.clear();
	indicies.clear();
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
	rendObjs[index].rotation =
		glm::eulerAngleXYZ(rotation.y * 0.005f, rotation.x * 0.005f, rotation.z * 0.005f);
}

void Renderer::set_rendMassPoint_rotation(u32 index, vec3 rotation)
{
	rendMassPoints[index].rotation =
		glm::eulerAngleXYZ(rotation.y * 0.005f, rotation.x * 0.005f, rotation.z * 0.005f);
}

void Renderer::set_all_rendable_rotation(vec3 rotation)
{
	for (u32 i = 0; i < rendObjs.size(); i++)
		set_rendObj_rotation(i, rotation);

	for (u32 i = 0; i < rendMassPoints.size(); i++)
		set_rendMassPoint_rotation(i, rotation);
}

void Renderer::set_rendMassPoint_position(u32 index, vec3 position)
{
	rendMassPoints[index].position = position;
}

Camera* Renderer::getCamera()
{
	return camera;
}