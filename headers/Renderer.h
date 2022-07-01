#pragma once
#include "Types.h"

#include "Mesh.h"
#include "Model.h"

struct RendObj
{
	u32 startIndex;
	u32 endIndex;

	mat4 transformation;
};

class Renderer
{
private:
	GLuint VBO;				// Vertex Buffer Object
	GLuint NBO;				// Normal Buffer Object
	GLuint TCBO;			// Texture Coordinate Buffer Object
	GLuint EBO;				// Element Array Buffer Object

	GLuint VAO;				// Vertex Array Pointer

	GLuint programId;

	std::vector<glm::vec3> positions;
	std::vector<u32> indicies;

	std::vector<RendObj> rendObjs;

public:
	vec4 clear_color;

public:
	Renderer();
	~Renderer();

	void init();
	void draw();

	void genGLBuffers();

	void addObject(Mesh *mesh);
	void addMeshScene(Model* meshScene);

	// Update variables
	void update_clear_color(vec4 color);

	// Getters
};

