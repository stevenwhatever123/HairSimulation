#include "pch.h"
#include "Utils/Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image():
	data(NULL)
{

}

Image::~Image()
{

}

void Image::readImage(const char* path, int& width, int& height, int &numChannels)
{
	data = stbi_load(path, &width, &height, &numChannels, 0);

	if (!data)
	{
		printf("Cannot load texture\n");
	}
}

void Image::freeImage()
{
	if(data)
		stbi_image_free(data);
}