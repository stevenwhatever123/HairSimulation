#pragma once
#include <Managers/FileManager.h>
#include <Managers/HairManager.h>
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

	Renderer* renderer;

	std::vector<GLShader*> shaderPrograms;

	GLShader* currentProgram;

	// Hair Manager for this project
	HairManager* hairManager;

public:
	// For the model matrix
	vec3 modelRotation;

public:

	SystemManager();
	~SystemManager();

	// Initialise
	void init();
	void init_window();
	void init_shaders();
	void init_hair_manager();
	void init_renderer();

	// Updates
	void update();
	void update_inputs();
	void update_camera();
	void update_hair_manager();
	void update_renderer();

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