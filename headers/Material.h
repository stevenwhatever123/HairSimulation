#pragma once
#include "Types.h"

class Material
{
public:

	std::string name;
	
	vec3 color;

	// Texture?
	bool has_texture;
	std::string texture_name;

public:
	Material();
	~Material();
};

