#pragma once

// Internal includes
#include "../component/Component.h"

#include "../render/Mesh.h"


namespace render
{
	class RenderComponent : public component::Component
	{
	public:
		
		/**
		 * Constructor 
		 * @author sascha blank
		 */
		RenderComponent( render::Mesh* p_mesh );

		/**
		 * Default Constructor
		 * @author sascha blank
		 */
		RenderComponent();

		/**
		 * Virtual destructor
		 */
		virtual ~RenderComponent(void);

		// The mesh to render
		render::Mesh* m_mesh;

		// the name of the meshfile
		std::string m_meshFileName;

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
