#pragma once

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"

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
		void receiveMessage( component::Event* p_event );
	};
}