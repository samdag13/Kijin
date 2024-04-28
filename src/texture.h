#pragma once
#include "gfx_core.h"

class Texture
{
private:
	unsigned int RendererID;
	std::string Filepath;
	unsigned char* LocalBuffer;
	int Width, Heigth, BPP;

public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int getWidth() const { return Width; }
	inline int getHeigth() const { return Heigth; }
};