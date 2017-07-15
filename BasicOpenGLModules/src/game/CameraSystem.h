#pragma once

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"
#include "../Camera.h"

namespace game
{
	/**
	 * System to manage the Camera. 
	 * This system processes the CameraEvent
	 * @author sascha blank
	 */
	class CameraSystem : public component::System
	{
	public:

		/**
		 * Default Constructor
		 * @author sascha blank
		 */
		CameraSystem( void );

		/**
		 * Virtual destructor
		 * @author sascha blank
		 */
		virtual ~CameraSystem( void );

		/**
		 * Update function which gets call in every cycle of the mainloop
		 * @author sascha blank
		 */
		void update();

		/**
		 * Receive and process Events.
		 * In this case the used Event is the CameraEvent
		 * @author sascha blank
		 * @param Event*, pointer on the event to process
		 */
		void receiveEvent( component::Event* p_event );

	private:

		// Camera Pointer.
		Camera* m_camera;
	};
}