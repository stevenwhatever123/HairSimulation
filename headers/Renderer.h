#pragma once
#include "Types.h"

#include "Camera.h"
#include "GLShader.h"
#include "Mesh.h"
#include "Model.h"
#include "Material.h"
#include  "MassPoint.h"

struct RendObj
{
	vec3 position;

	u32 startIndex;
	u32 endIndex;

	mat4 translation;
	mat4 rotation;
	mat4 scaling;

	u32 primitive;

	u32 material_index;

	bool isMesh;
	bool isMassPoint;

	mat4 getTransformation() { return this->translation * this->rotation * this->scaling; }
};

struct RendMassPoint : RendObj
{
	// This will only use when isMassPoint is true
	u32 mass_point_id;
};

class Renderer
{
private:

	Camera* camera;

	GLuint VBO;				// Vertex Buffer Object
	GLuint NBO;				// Normal Buffer Object
	GLuint TCBO;			// Texture Coordinate Buffer Object
	GLuint EBO;				// Element Array Buffer Object

	GLuint UBO;				// Uniform buffer

	GLuint VAO;				// Vertex Array Pointer

	std::vector<GLShader*> shaderPrograms;

	mat4 projectionMatrix;

	std::vector<vec3> positions;
	std::vector<vec3> normals;
	std::vector<vec2> texCoords;
	std::vector<u32> indicies;

	std::vector<RendObj> rendObjs;
	std::vector<RendMassPoint> rendMassPoints;
	std::vector<MaterialUniform> rendMaterials;

	std::vector<Material> materials;

	u32 mass_point_count;

public:

	int width, height;		// Width and height of the framebuffer
	vec4 clear_color;

	mat4 rotation;

public:
	Renderer(int width, int height, Camera *camera);
	~Renderer();

	void init();
	void setFramebufferSize(int width, int height);

	void addShaderPrograms(const std::vector<GLShader*>& shaderPrograms);

	void draw();

	void genGLBuffers();

	void addObject(Mesh *mesh);
	void addMassPoint(Mesh* mesh);
	void addMaterial(Material* material);
	void addMeshScene(Model* meshScene);

	// Set variables
	void set_clear_color(vec4 color);
	void set_rendObj_rotation(u32 index, vec3 rotation);
	void set_rendMassPoint_rotation(u32 index, vec3 rotation);
	void set_all_rendable_rotation(vec3 rotation);

	void set_rendMassPoint_position(u32 index, vec3 position);

	// Getters
	Camera* getCamera();
};

