#include "pch.h"

#include "Mesh.h"

Mesh::Mesh() :
	name(""),
	isMesh(false),
	isSkull(false),
	isMassPoint(false),
	positions(),
	normals(),
	texCoords(),
	indicies(),
	primitive_type(0),
	material_index(0),
	mass_point_id(0),
	VBO(0),
	NBO(0),
	TCBO(0),
	EBO(0)
{

}

Mesh::~Mesh()
{

}

void Mesh::generateBuffers(GLShader* program, u32 shaderIndex)
{
	this->shaderIndex = shaderIndex;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &NBO);
	glGenBuffers(1, &TCBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	// Position Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		positions.size() * sizeof(vec3),
		positions.data(),
		GL_STATIC_DRAW);

	GLShader* shaderProgram = program;

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

void Mesh::updateBuffers()
{

}

void Mesh::clear_cpu_memory()
{
	positions.clear();
	normals.clear();
	texCoords.clear();
	indicies.clear();
}