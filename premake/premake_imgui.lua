project "imgui"
	filename "imgui"
	kind "StaticLib"
	language "C++"
	targetdir "../libraries/compiled_libraries/imgui"
	location "../project_files/"

	includedirs {"../libraries/imgui/"}

	vpaths {

		['Header Files'] = {
			"../libraries/imgui/*.h"
		},

		["Source Files"] = {
			"../libraries/imgui/*.cpp"
		}
	}

	files
	{
		"../libraries/imgui/*.cpp",
		"../libraries/imgui/*.h"
	}

	defines {
		"WIN32",
		"_WINDOWS"
	}
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
