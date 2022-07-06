#include "pch.h"
#include "GLShader.h"

GLShader::GLShader() :
	programId(0)
{
	
}

GLShader::GLShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	loadShader(vertexShaderPath, fragmentShaderPath);
}

GLShader::~GLShader()
{

}

void GLShader::loadShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader ode from file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else
	{
		printf("Failed to read vertex shader: %s\n", vertexShaderPath);
		return;
	}

	// Read fragment shader code from file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentShaderPath, std::ios::in);
	if (fragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}
	else
	{
		printf("Failed to read fragment shader: %s\n", fragmentShaderPath);
		return;
	}

	GLint ret = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader: %s\n", vertexShaderPath);
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderId, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderId);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &ret);
	glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	if (ret == GL_FALSE)
	{
		printf("Error compiling vertex shader: %s\n", vertexShaderPath);
		return;
	}

	// Compile Fragment Shader
	printf("Compiling shader: %s\n", fragmentShaderPath);
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderId);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &ret);
	glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderId, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	if(ret == GL_FALSE)
	{
		printf("Error compiling fragment shader: %s\n", fragmentShaderPath);
		return;
	}

	// Link the program
	printf("Linking program\n");
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	// Check the program
	glGetProgramiv(programId, GL_LINK_STATUS, &ret);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	if (ret == GL_FALSE)
	{
		printf("Erorr linking the program\n");
		return;
	}

	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	printf("Program linked successfully\n");
}

void GLShader::use()
{
	glUseProgram(programId);
}

void GLShader::setUniformVec3(const char* name, const vec3& value)
{
	GLuint uniformId = glGetUniformLocation(this->programId, name);

	glUniform3fv(uniformId, 1, glm::value_ptr(value));
}

void GLShader::setUniformMat4(const char* name, const mat4& value)
{
	GLuint uniformId = glGetUniformLocation(this->programId, name);

	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
}

void GLShader::setUniformMaterial(GLuint uniformIndex, const MaterialUniform& rendMaterial)
{	
	glBindBuffer(GL_UNIFORM_BUFFER, uniformIndex);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(MaterialUniform), &rendMaterial);

	//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(bool), &rendMaterial.has_texture);
	//glBufferSubData(GL_UNIFORM_BUFFER, 4 * 4, sizeof(vec4), &rendMaterial.color[0]);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

GLuint GLShader::getAttribLocation(const char* attribute)
{
	return glGetAttribLocation(this->programId, attribute);
}