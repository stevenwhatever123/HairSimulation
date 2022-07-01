#pragma once
#include <Managers/FileManager.h>
#include <Utils/ModelLoader.h>
#include <GLShader.h>
#include <Renderer.h>

class SystemManager
{
private:
	GLFWwindow* window;
	Renderer* renderer;

	std::vector<GLShader*> shaderPrograms;

	GLShader* currentProgram;

public:

	SystemManager();
	~SystemManager();

	// Initialise
	void init();
	void init_window();
	void init_shaders();
	void init_renderer();

	// Updates
	void update();
	void update_inputs();
	void update_renderer();

	// Utils
	void readFile();

	// Keyboard / Mouse
	unsigned int keys[256];

	// Return
	bool closeWindow;
	bool shouldCloseWindow() const { return closeWindow; };
};