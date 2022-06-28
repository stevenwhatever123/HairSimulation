#pragma once
#include <Managers/FileManager.h>
#include <Utils/ModelLoader.h>

class SystemManager
{
private:
	GLFWwindow* window;

public:

	SystemManager();
	~SystemManager();

	// Initialise
	void init();
	void init_window();

	// Updates
	void update();
	void update_inputs();

	// Utils
	void readFile();

	// Keyboard / Mouse
	unsigned int keys[256];

	// Return
	bool closeWindow;
	bool shouldCloseWindow() const { return closeWindow; };
};