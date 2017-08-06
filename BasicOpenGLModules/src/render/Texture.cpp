#include <SDL2\SDL_image.h>
#include <iostream>

#include "Texture.h"

using namespace render;

Texture::Texture(const char* p_filename)
{
	m_texture = IMG_Load( p_filename );
	if (m_texture == nullptr)
	{
		std::cout << "Texturefile not foung" << std::endl;
	}
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	int Mode = GL_RGB;

	if (m_texture->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	/*glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );*/
	// set texture filtering parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	glTexImage2D( GL_TEXTURE_2D, 0, Mode, m_texture->w, m_texture->h, 0, Mode, GL_UNSIGNED_BYTE, m_texture->pixels );
	glGenerateMipmap( GL_TEXTURE_2D );

	SDL_FreeSurface( m_texture );
}


Texture::~Texture()
{
	delete m_texture;
	glDeleteTextures( 1, &m_textureID );
}


GLuint Texture::getTextureID(void)
{
	return m_textureID;
}