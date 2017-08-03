#include <SDL2\SDL_image.h>



#include "CubeMapTexture.h"

using namespace render;
using namespace std;

CubeMapTexture::CubeMapTexture( const std::vector<std::string>& p_paths)
{

	glGenTextures( 1, &m_textureID );
	glBindTexture( GL_TEXTURE_CUBE_MAP, m_textureID );
	for (int i = 0; i < p_paths.size(); ++i)
	{

		SDL_Surface* l_texture = IMG_Load( p_paths[ i ].c_str() );
		if (l_texture != nullptr)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, l_texture->w, l_texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, l_texture->pixels);
			SDL_FreeSurface( l_texture );
		}
		else
		{
			bool test = false;
		}
	}

	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
	/*int width, height, nrChannels;
	unsigned char *data;
	for (GLuint i = 0; i < textures_faces.size(); i++)
	{
		data = stbi_load( textures_faces[ i ].c_str(), &width, &height, &nrChannels, 0 );
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);
	}*/
}


CubeMapTexture::~CubeMapTexture( )
{

}

GLuint CubeMapTexture::getTextureID()
{
	return m_textureID;
}



