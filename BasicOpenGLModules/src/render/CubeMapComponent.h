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
		Mesh* skyboxMesh;
		CubeMapTexture* m_texture;
		GLuint m_shaderID;
	};
}
