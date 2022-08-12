#pragma once
#include <Managers/FileManager.h>
#include <Managers/HairManager.h>
#include <Managers/CollisionManager.h>
#include <Utils/ModelLoader.h>
#include <GLShader.h>
#include <Renderer.h>
#include <Model.h>


class SystemManager
{
private:
	GLFWwindow* window;
	int width, height;

	double mouseX, mouseY;			// Current mouse xy position

	f64 currentTime;
	f64 deltaTime;
	f64 lastTime;

	u64 frameCount = 0;
	f64 timePasses = 0;
	f64 fpsAverage = 0;

public:
	bool simulate;

	// For the model matrix
	vec3 modelRotation;

	Renderer* renderer;

	std::vector<GLShader*> shaderPrograms;

	GLShader* currentProgram;

	// Hair Manager for this project
	HairManager* hairManager;

	// Manager for handling collision
	CollisionManager* collisionManager;

	std::vector<Model*> models;

public:

	SystemManager();
	~SystemManager();

	// Initialise
	void init();
	void init_window();
	void init_shaders();
	void init_hair_manager();
	void init_collision_manager();
	void init_renderer();
	void init_imgui();


	// Updates
	void update();
	void update_inputs();
	void update_camera();
	void update_hair_manager(f64 deltaTime);
	void update_collision_manager();
	void update_renderer();
	void update_imgui();

	// Utils
	void readFile();
	void loadModel();

	// Keyboard / Mouse
	unsigned int keys[256];
	
	bool left_mouse_clicked;
	bool right_mouse_clicked;

	// Return
	bool closeWindow;
	bool shouldCloseWindow() const { return closeWindow; };

	// Print / Debug / Log
	void printModelDetails(const Model &modelScene);
};