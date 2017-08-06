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
		virtual ~CubeMapComponent();

		GLuint skyboxVAO;
		GLuint skyboxVBO;
		CubeMapTexture* m_texture;
		std::string m_shaderName;

		/**
		 * Abstract function to serialize the component.
		 * It uses a xml format.
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the node to append the component node
		 */
		void serialize( rapidxml::xml_node<>* p_rootNode );

		/**
		 * Function to read the component data from a xml node
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the component node
		 */
		void deserialize( rapidxml::xml_node<>* p_node );
	};
}
