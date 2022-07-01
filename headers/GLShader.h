#pragma once
#include "Types.h"

namespace SystemUtils
{
	// Load, compile and link shader program with the renderer
	GLuint loadShader(const char* vertexShaderPath, const char* fragmentShaderPath);
}