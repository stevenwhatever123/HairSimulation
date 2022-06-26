project "glm"
	filename "glm"
	kind "StaticLib"
	language "C++"
	targetdir "../libraries/compiled_libraries/glm"
	location "../project_files/"

	includedirs {"../libraries/glm/"}

	files
	{
		"../libraries/glm/glm/**.hpp",
		"../libraries/glm/glm/**.cpp",
		"../libraries/glm/glm/**.inl"
	}

	defines {
		"WIN32",
		"_WINDOWS"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
