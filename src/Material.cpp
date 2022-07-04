#include "pch.h"
#include "Material.h"

Material::Material() :
	color(0),
	name(""),
	has_texture(false),
	texture_name(""),
	width(0),
	height(0),
	numChannels(0),
	texture_image(),
	texture_id(-1)
{

}

Material::~Material()
{

}

void Material::setTextureImage(Image *image)
{
	this->texture_image = image;
}

void Material::freeTextureImage()
{
	texture_image->freeImage();
	delete this->texture_image;
}

const char* Material::getTexturePath()
{
	return texture_name.c_str();
}

MaterialUniform Material::getMaterialUniform()
{
	MaterialUniform material_uniform{};
	material_uniform.has_texture = (u32) this->has_texture;
	material_uniform.color = this->color;
	
	return material_uniform;
}