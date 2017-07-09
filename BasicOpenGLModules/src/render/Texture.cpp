
#include "Texture.h"

Texture::Texture(const char* p_filename)
{
	m_texture = SDL_LoadBMP(p_filename);
	if (m_texture == nullptr)
	{
		bool a_test = false;
	}
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	int Mode = GL_RGB;

	if (m_texture->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, m_texture->w, m_texture->h, 0, Mode, GL_UNSIGNED_BYTE, m_texture->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


Texture::~Texture()
{
	SDL_FreeSurface(m_texture);
	delete m_texture;
}


GLuint Texture::getTextureID(void)
{
	return m_textureID;
}