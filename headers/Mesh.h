#pragma once
#include "Types.h"

#include "GLShader.h"

class Mesh
{
public:
	std::string name;

	bool isMesh;
	bool isSkull;
	bool isMassPoint;

	// This will only use when isMassPoint is true
	u32 mass_point_id;

	std::vector<vec3> positions;
	std::vector<vec3> normals;
	std::vector<vec2> texCoords;
	std::vector<u32> indicies;

	u32 primitive_type;

	u32 material_index;

	u32 shaderIndex;
	GLuint VBO;							// Vertex Buffer Object
	GLuint NBO;							// Normal Buffer Object
	GLuint TCBO;						// Texture Coordinate Buffer Object
	GLuint EBO;							// Element Array Buffer Object

	GLuint VAO;

public:

	Mesh();
	~Mesh();


	void generateBuffers(GLShader* program, u32 shaderIndex);
	void updateBuffers();

	void clear_cpu_memory();
};