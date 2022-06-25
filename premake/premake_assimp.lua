

externalproject "zlib"
	location "../libraries/build_assimp/contrib/zlib/"
	filename "zlibstatic"
	kind "StaticLib"
	language "C++"
	targetdir "../libs/compiled_libs/assimp/Debug/"



externalproject "Assimp"
  location "../libraries/build_assimp/code/"
  filename "assimp"
  kind "StaticLib"
  language "C++"


  config_file = io.readfile("../libraries/assimp/include/assimp/config.h.in"):gsub("#cmakedefine .", "// fuck you ")
  io.writefile("../libraries/assimp/include/assimp/config.h", config_file)

  targetdir "../libraries/compiled_libs/assimp"

  if _ACTION ~= 'clean_up' and _ACTION ~= 'clean_up_full'  then
	  os.executef('cmake --log-level NOTICE -G %q -B%s -S%s -D %s -D %s -D %s -D %s -D %s',
		  "Visual Studio 17 2022",
		  "../libraries/build_assimp/",
		  "../libraries/assimp/",
		  "BUILD_SHARED_LIBS:BOOL=ON",
		  "ASSIMP_BUILD_ZLIB=ON",
		  'ASSIMP_ARCHIVE_OUTPUT_DIRECTORY:STRING=../../compiled_libraries/assimp',
		  'ASSIMP_LIBRARY_OUTPUT_DIRECTORY:STRING=../../compiled_libraries/assimp',
		  'ASSIMP_RUNTIME_OUTPUT_DIRECTORY:STRING=../../compiled_libraries/assimp'
	  )
  end

  dependson {
	  "zlib"
  }

  filter "configurations:Debug"
	  runtime "Debug"
	  symbols "on"



