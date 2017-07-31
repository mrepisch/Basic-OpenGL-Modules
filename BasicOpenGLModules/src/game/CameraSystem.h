#pragma once

// External includes
#include <glew\GL\glew.h>

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"
#include "CameraComponent.h"

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
		CameraSystem( component::EntityCollection* p_collection);

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

		/**
		 * After the CameraEvent is processed the camera needs to be updated.
		 * @author sascha blank
		 * @param CameraComponent*, the component to update
		 */
		void updateCamera( CameraComponent* p_cameraComp );
	};
}