#pragma once
#include <Managers/SystemManager.h>

namespace SystemUI
{
	void init_imgui(GLFWwindow* window);
	void update_imgui(SystemManager *sys);
}