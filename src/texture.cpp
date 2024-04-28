#include "texture.h"
#include <stb_image.h>

Texture::Texture(const std::string &path)
	: RendererID(0), Filepath(path), m_localBuffer(nullptr), m_Width(0), m_Heigth(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	LocalBuffer = stbi_load(path.c_str(), &Width, &Heigth, &BPP, 4);

	GLCall(glGenTextures(1, &RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));

	// These 4 parameters need to be set for the texture to be shown, otherwise it's going to be a black texture
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (LocalBuffer)
		stbi_image_free(LocalBuffer);
}

Texture::~Texture()
{

	GLCall(glDeleteTextures(1, &RendererID));
}

void Texture::Bind(unsigned int slot) const
{

	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
