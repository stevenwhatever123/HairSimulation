#pragma once

class SystemManager
{
private:
	GLFWwindow* window;
	bool closeWindow;

public:

	SystemManager();
	~SystemManager();

	// Initialise
	void init();
	void init_window();

	// Updates
	void update();

	// Return
	bool shouldCloseWindow() const { return closeWindow; };
};