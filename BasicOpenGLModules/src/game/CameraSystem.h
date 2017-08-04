#pragma once

// External includes
#include <glew\GL\glew.h>

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"
#include "CameraComponent.h"



namespace game
{
	// Prototypes
	class CameraEvent;

	/**
	 * This System manages CameraComponents. At the moment there is just a ego perspectiv Camera impelementet.
	 * The positions and rotation of the camera is given by the CameraEvents.
	 * ! There is usualy just one CameraComponent at the time active. !
	 * Expect strange behavhior if you have 2 or more CameraComponents active.
	 * But you coid switch between Entitys which holds a CameraComponent in order to place multiple Cameras in the szene.
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
		 * Function to calculate the new Camera position depending on de input direction and velocity
		 * @author sascha blank
		 * @param CamaeraComponent* the camera compontent
		 * @param CameraEvent* the event which was incoming from the dispatcher
		 */
		void newPositionFromEvent( CameraComponent* p_cameraComp, CameraEvent* p_event );

		/**
		 * Function to calculate the cameras new rotation depending on the input offset
		 * @author sascha blank
		 * @param CameraComponent* camera component pointer
		 * @param CameraEvent* the event which was incoming from the dispatcher
		 */
		void addRotationFromEvent( CameraComponent* p_cameraComp, CameraEvent* p_event );

		/**
		 * After the CameraEvent is processed the camera needs to be updated.
		 * @author sascha blank
		 * @param CameraComponent*, the component to update
		 */
		void updateCamera( CameraComponent* p_cameraComp );
	};
}