#pragma once
#include "Types.h"

class GLShader
{
private:
	GLuint programId;

public:

public:
	GLShader();
	GLShader(const char* vertexShaderPath, const char* fragmentShaderPath);

	~GLShader();

	// Load, compile and link shader program with the renderer
	void loadShader(const char* vertexShaderPath, const char* fragmentShaderPath);

	// Command funtions
	void use();
	void setUniformMat4(const char* name, const mat4& value);

	// Getters
	GLuint getAttribLocation(const char* attribute);
};