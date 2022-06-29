#include "pch.h"
#include "Renderer.h"

Renderer::Renderer():
	clear_color(0)
{

}

Renderer::~Renderer()
{

}

void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);

	clear_color.x = 0.0f;	// R
	clear_color.y = 1.0f;	// G
	clear_color.z = 0.0f;	// B
	clear_color.w = 1.0f;	// A

	glClearColor(
		clear_color.x,
		clear_color.y,
		clear_color.z,
		clear_color.w
	);
}

void Renderer::draw()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::genVertexBuffer()
{
	
}

void Renderer::addObject(Mesh* mesh)
{

}

void Renderer::update_clear_color(vec4 color)
{
	clear_color.x = 0.0f;	// R
	clear_color.y = 1.0f;	// G
	clear_color.z = 0.0f;	// B
	clear_color.w = 1.0f;	// A

	glClearColor(
		clear_color.x,
		clear_color.y,
		clear_color.z,
		clear_color.w
	);
}