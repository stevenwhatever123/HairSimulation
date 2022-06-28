newaction {
	trigger = "clean_up",
	description = "Clean up files gen",
	execute = function()
		os.rmdir('build')
		os.rmdir('obj')
		os.rmdir('project_files')
		os.rmdir('x64')
		os.rmdir('.vs')
		os.remove('*.sln')
		os.remove('*.vcxproj*')
	end
}


workspace "HairSimulation"
	configurations {"Debug", "Release"}
	architecture "x64"
	startproject "HairSimulation"

include "premake/premake_glfw.lua"
include "premake/premake_assimp.lua"
include "premake/premake_glm.lua"

project "HairSimulation"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir "bin/%{cfg.buildcfg}"

	defines {"NOMINMAX"}
	disablewarnings {"4005"}

	filter "configurations:Debug"
	defines {"DEBUG"}
	symbols "on"

	includedirs
	{
		"",
		"headers",
		"libraries/glfw/include",
		"libraries/assimp/include",
		"libraries/glm/",
	}

	dependson
	{
		"glfw",
		"assimp",
		"glm",
	}

	links
	{
		"user32",
		"opengl32",
		"glfw",
		"assimp",
		"glm"
	}

	vpaths
	{
		["Headers"]					= {"headers/*.h"},

		["Precompiled Headers"]		= {"*.h", "*.cpp"},

		["Source Files"]			= {"src/*.cpp"}
	}

	files
	{
		"headers/**.h",
		"src/**.cpp",
		"*.h",
		"*.cpp"
	}

	pchheader "pch.h"
	pchsource "pch.cpp"

			postbuildcommands { '{COPYFILE} "%{wks.location}/libraries/compiled_libraries/assimp/Debug/assimp-vc143-mtd.dll" %{cfg.targetdir}'  }