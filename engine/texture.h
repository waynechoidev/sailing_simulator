#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char *fileLoc);

	bool loadTextureRGB();
	bool loadTextureRGBA();

	void useTexture();
	void clearTexture();

	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char *fileLocation;
};
