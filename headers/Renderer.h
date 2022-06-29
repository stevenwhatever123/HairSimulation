#pragma once
#include "Types.h"

#include "Mesh.h"

class Renderer
{
public:
	vec4 clear_color;

public:
	Renderer();
	~Renderer();

	void init();
	void draw();

	void genVertexBuffer();

	void addObject(Mesh *mesh);

	// Update variables
	void update_clear_color(vec4 color);
};

