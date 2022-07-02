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
	VAO(-1),
	projectionMatrix(1),
	clear_color(0),
	positions(),
	normals(),
	texCoords(),
	indicies(),
	rendObjs()
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

	set_clear_color(vec4(0.4f, 0.4f, 0.4f, 1));

	// Set projection matrix
	projectionMatrix = glm::perspective(
		glm::radians(90.0f),
		4.0f/ 3.0f,
		0.1f,
		100.0f
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

void Renderer::setShaderProgram(GLShader* shaderProgram)
{
	// Set shader program
	this->shaderProgram = shaderProgram;
}

void Renderer::draw()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	glBindVertexArray(VAO);

	shaderProgram->setUniformMat4("viewMatrix", camera->getTransformation());
	shaderProgram->setUniformMat4("projectionMatrix", projectionMatrix);

	for (RendObj &renderObject : rendObjs)
	{
		shaderProgram->setUniformMat4("modelMatrix", renderObject.getTransformation());

		glDrawElements(
			renderObject.primitive, 
			renderObject.endIndex - renderObject.startIndex, 
			GL_UNSIGNED_INT, 
			(void*) (renderObject.startIndex * sizeof(u32)));
	}
}

void Renderer::genGLBuffers()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &NBO);
	glGenBuffers(1, &TCBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
}

void Renderer::addObject(Mesh* mesh)
{
	RendObj renderObject;
	renderObject.translation = mat4(1);
	renderObject.rotation = mat4(1);
	renderObject.scaling = mat4(1);
	renderObject.startIndex = indicies.size();
	renderObject.primitive = mesh->primitive_type;

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

void Renderer::addMeshScene(Model* meshScene)
{
	for (Mesh* mesh : meshScene->meshes)
	{
		addObject(mesh);
	}

	// Clear mesh data from cpu
	positions.clear();
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

void Renderer::set_all_rendObj_rotation(vec3 rotation)
{
	for (u32 i = 0; i < rendObjs.size(); i++)
		set_rendObj_rotation(i, rotation);
}

Camera* Renderer::getCamera()
{
	return camera;
}