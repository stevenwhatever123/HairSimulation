#pragma once
#include <Managers/SystemManager.h>

namespace SystemUI
{
	void init_imgui(GLFWwindow* window);
	void update_imgui(SystemManager *sys);

	void import_head_handle(SystemManager* sys);
	void single_strand(SystemManager* sys);
}