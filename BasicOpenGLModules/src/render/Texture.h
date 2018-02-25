#pragma once

// External includes
#include <SDL2\SDL.h>
#include <glew\GL\glew.h>

namespace render
{

	/**
	 * This class represents a Texture.
	 * Supported Picturetypes = BMP
	 * In the Constructor the Texture will be loaded with SDL and
	 * binds it to openGL
	 * @author sascha blank
	 */
	class Texture
	{
	public:

		/**
		 * Constructor
		 * @author sascha blank
		 * @param t_filename, the Texture file path to load
		 */
		Texture(const char* p_filename);

		/**
		 * Virutal destructor
		 * @author sascha blank
		 */
		virtual ~Texture();

		/**
		 * Get the ID of the texture in order to bind it in the render function
		 * @author sascha blank
		 */
		GLuint getTextureID(void);

		const char* getTexturePath();

	private:

		// Surface Pointer which is the texture
		SDL_Surface* m_texture;

		// The texture id 
		GLuint m_textureID;

		const char* m_texturePath;
	};
}