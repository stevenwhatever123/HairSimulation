#pragma once
#include "Types.h"

#include "Camera.h"
#include "GLShader.h"
#include "Mesh.h"
#include "Model.h"

struct RendObj
{
	u32 startIndex;
	u32 endIndex;

	mat4 translation;
	mat4 rotation;
	mat4 scaling;

	u32 primitive;

	mat4 getTransformation() { return translation* rotation* scaling; }
};

class Renderer
{
private:

	Camera* camera;

	GLuint VBO;				// Vertex Buffer Object
	GLuint NBO;				// Normal Buffer Object
	GLuint TCBO;			// Texture Coordinate Buffer Object
	GLuint EBO;				// Element Array Buffer Object

	GLuint VAO;				// Vertex Array Pointer

	GLShader *shaderProgram;

	mat4 projectionMatrix;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<u32> indicies;

	std::vector<RendObj> rendObjs;

public:

	int width, height;		// Width and height of the framebuffer
	vec4 clear_color;

public:
	Renderer(int width, int height, Camera *camera);
	~Renderer();

	void init();
	void setFramebufferSize(int width, int height);
	void setShaderProgram(GLShader* shaderProgram);

	void draw();

	void genGLBuffers();

	void addObject(Mesh *mesh);
	void addMeshScene(Model* meshScene);

	// Set variables
	void set_clear_color(vec4 color);
	void set_rendObj_rotation(u32 index, vec3 rotation);
	void set_all_rendObj_rotation(vec3 rotation);

	// Getters
	Camera* getCamera();
};

