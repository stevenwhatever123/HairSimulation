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
include "premake/premake_glad.lua"

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
		"libraries/glad/include",
	}

	dependson
	{
		"glfw",
		"assimp",
		"glm",
		"glad",
	}

	links
	{
		"user32",
		"opengl32",
		"glfw",
		"assimp",
		"glm",
		"glad",
	}

	vpaths
	{
		["Headers"]					= {"headers/*.h"},
		["Headers/Managers"]		= {"headers/Managers/*.cpp"},
		["Headers/Utils"]			= {"headers/Utils/*.cpp"},

		["Precompiled Headers"]		= {"*.h", "*.cpp"},

		["Source Files"]			= {"src/*.cpp"},
		["Source Files/Managers"]	= {"src/Managers/*.cpp"},
		["Source Files/Utils"]		= {"src/Utils/*.cpp"},
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