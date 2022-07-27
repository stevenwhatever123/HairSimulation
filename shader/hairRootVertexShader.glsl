#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform vec3 u_position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) out vec4 oPosition;
layout(location = 1) out vec3 oNormal;
layout(location = 2) out vec2 oTexCoord;

void main()
{
	oNormal = vec3(modelMatrix * vec4(normal, 1));
	oTexCoord = texCoord;

	gl_PointSize = 5.0f;

	oPosition = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
	gl_Position = oPosition;
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(u_position, 1);
}