#version 450 core

layout(location = 0) in vec3 position;

uniform mat4 projectionMatrix;

void main()
{
	// Model Matrix
	mat4 translationMatrix;
	translationMatrix[0][0] = 1;
	translationMatrix[1][1] = 1;
	translationMatrix[2][2] = 1;
	translationMatrix[3][3] = 1;

	translationMatrix[3][0] = 0;
	translationMatrix[3][1] = 0;
	translationMatrix[3][2] = -50;

	gl_Position = translationMatrix * vec4(position, 1);
}