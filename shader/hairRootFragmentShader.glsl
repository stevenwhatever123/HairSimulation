#version 450 core

layout(location = 0) in vec3 normal;
layout(location = 1) in vec2 texCoord;

layout(location = 0) out vec4 oColor;

void main()
{
	//gl_PointSize = 5.0f;

	oColor = vec4(0, 0, 0, 1);
}