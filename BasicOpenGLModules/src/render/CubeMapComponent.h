#pragma once

#include "../component/Component.h"
#include "Mesh.h"
#include "CubeMapTexture.h"


namespace render
{
	class CubeMapComponent : public component::Component
	{
	public:
		CubeMapComponent();


		GLuint skyboxVAO;
		GLuint skyboxVBO;
		CubeMapTexture* m_texture;
		GLuint m_shaderID;
	};
}
