#pragma once

#include "Base.h"


class Texture
{
public:
	Texture(const std::string& filePath);
	Texture(void* data, int32 width, int32 height, int32 format);
	~Texture();

	void Bind(uint32 slot = 0U);
	void Unbind();

	int32 GetWidth() const { return Width; }
	int32 GetHeight() const { return Height; }

private:
	uint32 TextureID;
	int32 Width, Height, Channels;
};