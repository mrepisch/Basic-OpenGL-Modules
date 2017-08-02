#pragma once

// Internal includes
#include "System.h"

namespace component
{
	/**
	 * This system handels all manipulation of a TranslationComponent.
	 * That means the position, rotation and the scale of a Entity
	 * @author sascha blank
	 */
	class TranslationSystem : public System
	{
	public:

		/**
		 * Default constructor
		 * @author sascha blank
		 */
		TranslationSystem( EntityCollection* p_collection );

		/**
		 * Update function which is called in every cycle in the mainloop
		 * @author sascha blank
		 */
		void update();

		/**
		 * Function to receive events for processing it.
		 * @author sascha blank
		 * @param Event*, pointer on the event to process
		 */
		void receiveEvent( Event* p_event );
	};
}