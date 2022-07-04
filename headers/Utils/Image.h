#pragma once
class Image
{
public:
	unsigned char* data;

public:
	Image();
	~Image();

	void readImage(const char* path, int& width, int& height, int &numChannels);
	void freeImage();
};