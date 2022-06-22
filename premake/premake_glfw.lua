project "glfw"
	filename "glfw"
	kind "StaticLib"
	language "C++"
	targetdir "../libraries/compiled_libraries/glfw"
	location "../project_files/"

	includedirs {"../libraries/glfw/include"}

	vpaths {

		['Header Files'] = {
			"../libraries/glfw/include/GLFW/glfw3.h",
			"../libraries/glfw/include/GLFW/glfw3native.h",
			"../libraries/glfw/src/internal.h",
			"../libraries/glfw/src/mappings.h",
			"../libraries/glfw/src/null_joystick.h",
			"../libraries/glfw/src/null_platform.h",
			"../libraries/glfw/src/win32_platform.h",
			"../libraries/glfw/src/win32_joystick.h",
			"../libraries/glfw/src/win32_thread.h",
			"../libraries/glfw/src/win32_time.h"
		},

		["Source Files"] = {

			"../libraries/glfw/src/context.c",
			"../libraries/glfw/src/egl_context.c",
			"../libraries/glfw/src/init.c",
			"../libraries/glfw/src/input.c",
			"../libraries/glfw/src/monitor.c",
			"../libraries/glfw/src/null_init.c",
			"../libraries/glfw/src/null_joystick.c",
			"../libraries/glfw/src/null_monitor.c",
			"../libraries/glfw/src/null_window.c",
			"../libraries/glfw/src/osmesa_context.c",
			"../libraries/glfw/src/platform.c",
			"../libraries/glfw/src/vulkan.c",
			"../libraries/glfw/src/wgl_context.c",
			"../libraries/glfw/src/window.c",

			"../libraries/glfw/src/win32_init.c",
			"../libraries/glfw/src/win32_joystick.c",
			"../libraries/glfw/src/win32_module.c",
			"../libraries/glfw/src/win32_monitor.c",
			"../libraries/glfw/src/win32_thread.c",
			"../libraries/glfw/src/win32_time.c",
			"../libraries/glfw/src/win32_window.c",
		}
	}

	files
	{
		"../libraries/glfw/include/GLFW/glfw3.h",
		"../libraries/glfw/include/GLFW/glfw3native.h",
		"../libraries/glfw/src/internal.h",
		"../libraries/glfw/src/mappings.h",
		"../libraries/glfw/src/null_joystick.h",
		"../libraries/glfw/src/null_platform.h",
		"../libraries/glfw/src/win32_platform.h",
		"../libraries/glfw/src/win32_joystick.h",
		"../libraries/glfw/src/win32_thread.h",
		"../libraries/glfw/src/win32_time.h",

		"../libraries/glfw/src/context.c",
		"../libraries/glfw/src/egl_context.c",
		"../libraries/glfw/src/init.c",
		"../libraries/glfw/src/input.c",
		"../libraries/glfw/src/monitor.c",
		"../libraries/glfw/src/null_init.c",
		"../libraries/glfw/src/null_joystick.c",
		"../libraries/glfw/src/null_monitor.c",
		"../libraries/glfw/src/null_window.c",
		"../libraries/glfw/src/osmesa_context.c",
		"../libraries/glfw/src/platform.c",
		"../libraries/glfw/src/vulkan.c",
		"../libraries/glfw/src/wgl_context.c",
		"../libraries/glfw/src/window.c",

		"../libraries/glfw/src/win32_init.c",
		"../libraries/glfw/src/win32_joystick.c",
		"../libraries/glfw/src/win32_module.c",
		"../libraries/glfw/src/win32_monitor.c",
		"../libraries/glfw/src/win32_thread.c",
		"../libraries/glfw/src/win32_time.c",
		"../libraries/glfw/src/win32_window.c",
	}

	defines {
		"_GLFW_WIN32",
		"_CRT_SECURE_NO_WARNINGS"
	}


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
