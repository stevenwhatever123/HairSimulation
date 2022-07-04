#pragma once
#include "Types.h"

#include "Utils/Image.h"

struct MaterialUniform
{
	// std140 layout
	vec4 color;
	u32 has_texture;			// Boolean 4 byte layout
};

class Material
{
public:

	std::string name;
	
	vec4 color;

	// Texture?
	bool has_texture;
	std::string texture_name;

	// Texture details
	
	int width, height, numChannels;
	Image* texture_image;
	GLuint texture_id;

public:
	Material();
	~Material();

	// Setters
	void setTextureImage(Image *image);
	
	void freeTextureImage();

	// Getters
	const char* getTexturePath();
	MaterialUniform getMaterialUniform();
};