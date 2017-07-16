#pragma once

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"
#include "../component/Entity.h"

namespace render
{
	class RenderSystem : public component::System
	{
	public:
		/**
		 * Constructor
		 * @author sascha blank
		 */
		RenderSystem();

		/**
		 * virtual destructor
		 */
		virtual ~RenderSystem();

		/**
		 * Update function which is called in the mainloop
		 * @author sascha blank
		 */
		void update();

		/**
		 * Function to receive and process Events form the event system
		 * @author sascha blank
		 */
		void receiveEvent( component::Event* p_event );

		GLuint getShaderProgramID();

	private:
		std::string m_vertexShader;
		std::string m_fragmentShader;
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
		GLuint m_shaderProgramID;

		component::Entity* m_camera;
	};
}