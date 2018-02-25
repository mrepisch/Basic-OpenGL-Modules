#pragma once

// Internal includes
#include "../component/Component.h"
#include "Mesh.h"
#include "CubeMapTexture.h"


namespace render
{
	/**
	 * CubeMapComponent which is uses to display a skybox. 
	 * This component will be processed by the RenderSystem
	 * @author sascha blank
	 */
	class CubeMapComponent : public component::Component
	{
	public:
		
		/**
		 * Default Constructor
		 * @author sascha blank
		 */
		CubeMapComponent();
		
		/**
		 * Virtual destructor
		 * @author sascha blank
		 */
		virtual ~CubeMapComponent();

		// The skyboy vertex array object id
		GLuint skyboxVAO;
		
		// Cubemap texture pointer
		CubeMapTexture* m_texture;

		// The shader name to use to render the Cubemap
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

	private:
		// The vertex buffer object id
		GLuint skyboxVBO;
	};
}
