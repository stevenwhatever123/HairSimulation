#version 450 core

layout(location = 0) in vec3 position;

void main()
{
	// Model Matrix
	mat4 translationMatrix;
	translationMatrix[0][0] = 1;
	translationMatrix[1][1] = 1;
	translationMatrix[2][2] = 1;
	translationMatrix[3][3] = 1;

	translationMatrix[3][0] = 0;
	translationMatrix[3][1] = -20;
	translationMatrix[3][2] = -50;

	// Projection Matrix
	//mat4 projectionMatrix = perspective(
	//	radians(90.0f),
	//	4.0f/3.0f,
	//	0.1f,
	//	100.0f
	//);
	


	gl_Position = translationMatrix * vec4(position, 1);
}