project "glad"
	kind "StaticLib"
	language "C"
	architecture "x64"

	targetdir "../libraries/compiled_libraries/glad"
    
  	includedirs { "../libraries/glad/include/" }

	files { "../libraries/glad/src/glad.c" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"