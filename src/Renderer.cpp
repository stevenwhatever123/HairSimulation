#include "pch.h"
#include "Renderer.h"
#include "GLShader.h"

Renderer::Renderer() :
	VBO(-1),
	NBO(-1),
	TCBO(-1),
	EBO(-1),
	VAO(-1),
	projectionMatrix(1),
	clear_color(0),
	positions(),
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

	// Set clear color
	clear_color.x = 0.0f;	// R
	clear_color.y = 1.0f;	// G
	clear_color.z = 0.0f;	// B
	clear_color.w = 1.0f;	// A

	glClearColor(
		clear_color.x,
		clear_color.y,
		clear_color.z,
		clear_color.w
	);

	// Set projection matrix
	projectionMatrix = glm::perspective(
		glm::radians(90.0f),
		4.0f / 3.0f,
		0.1f,
		100.0f
	);
}

void Renderer::setShaderProgram(GLShader* shaderProgram)
{
	// Set shader program
	//programId = SystemUtils::loadShader("shader/headVertexShader.glsl", "shader/headFragmentShader.glsl");
	this->shaderProgram = shaderProgram;
}

void Renderer::draw()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	shaderProgram->setUniformMat4("projectionMatrix", projectionMatrix);

	for (RendObj renderObject : rendObjs)
	{
		glDrawElements(
			GL_TRIANGLES, 
			renderObject.endIndex - renderObject.startIndex, 
			GL_UNSIGNED_INT, 
			(void*) (renderObject.startIndex * sizeof(u32)));
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	renderObject.startIndex = indicies.size();

	const u32 currentVerticesSize = positions.size();

	// Copy vertex position from mesh to the renderer
	copy(mesh->positions.begin(), mesh->positions.end(), std::back_inserter(positions));

	// Copy indicies
	for (u32 i = 0; i < mesh->indicies.size(); i++)
	{
		indicies.push_back(currentVerticesSize + mesh->indicies[i]);
	}

	renderObject.endIndex = indicies.size();

	rendObjs.push_back(renderObject);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		positions.size() * sizeof(vec3),
		positions.data(),
		GL_STATIC_DRAW);

	// Positions Attributions
	GLuint posAttri = shaderProgram->getAttribLocation("position");
	glVertexAttribPointer(
		posAttri,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexArrayAttrib(VAO, posAttri);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indicies.size() * sizeof(u32),
		indicies.data(),
		GL_STATIC_DRAW
	);

	std::cout << "Hello, I'm inside the renderer" << "\n";
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

void Renderer::update_clear_color(vec4 color)
{
	clear_color.x = 0.0f;	// R
	clear_color.y = 1.0f;	// G
	clear_color.z = 0.0f;	// B
	clear_color.w = 1.0f;	// A

	glClearColor(
		clear_color.x,
		clear_color.y,
		clear_color.z,
		clear_color.w
	);
}