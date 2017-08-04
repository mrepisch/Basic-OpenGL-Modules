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
		 * Virtual destructor
		 */
		virtual ~RenderComponent(void);

		// The mesh to render
		render::Mesh* m_mesh;

		void serialize( rapidxml::xml_node<>* p_rootNode ){}
	};
}
