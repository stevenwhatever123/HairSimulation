#pragma once

// stb
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

// C++ library
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <algorithm>
#include <iterator>

// Windows
#include <Windows.h>

// Glad
#include <glad/glad.h>

// GLFW
#include <glfw/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>