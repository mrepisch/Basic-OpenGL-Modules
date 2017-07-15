#pragma once

// Internal includes
#include "EntityCollection.h"
#include "Event.h"

namespace component
{
	enum EnSystem
	{
		e_undefinedSystem = 0,
		e_renderSystem,
		e_cameraSystem,
		e_translationSystem,
		e_inputSystem
	};

	/**
	 * Baseclass of all Systems.
	 * To inherit from this class you need to implement the update Function 
	 * and the constructor.
	 * And also you need to add a new entry in the enum.
	 * In general each System use one Componenttype.
	 * @author sascha blank
	 */
	class System
	{
	public:

		/**
		 * Constructor
		 * @author sascha blank
		 * @param p_system, Enum entry of the system
		 */
		System(EnSystem p_system);

		/**
		 * Returns the SystemtType enum definition of the system
		 * @author sascha blank
		 * @return EnSystem
		 */
		EnSystem getSystemType() const;

		/**
		 * Function to implement in the inherited system
		 * @author sascha blank
		 */
		virtual void update() = 0;

		/**
		 * Function to received messages which are send by the MessagesDispatcher.
		 * @author sascha blank
		 * @param Event*, pointer on the event object
		 */
		virtual void receiveEvent(Event* p_event) = 0;

	protected:

		/**
		 * Private copyconstructor
		 * @author sascha blank
		 */
		System( const System& t_other ) {}

		// The Sytem type definition
		EnSystem m_systemType;
	};
}