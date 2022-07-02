#version 450 core

layout(location = 0) in vec3 normal;
layout(location = 1) in vec2 texCoord;

layout(location = 0) out vec4 oColor;

void main()
{
	//oColor = vec4(1, 0, 0, 1);

	//oColor = vec4(texCoord, 0, 1);
	oColor = vec4(normal, 1);
}