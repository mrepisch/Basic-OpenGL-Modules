#pragma once
#include <vector>
#include <string>
#include <glew\GL\glew.h>


namespace render
{
	class CubeMapTexture
	{
	public:
		CubeMapTexture( const std::vector<std::string>& p_texturePaths );
		virtual ~CubeMapTexture();

		GLuint getTextureID();


	private:
		
		GLuint m_textureID;

	};
}