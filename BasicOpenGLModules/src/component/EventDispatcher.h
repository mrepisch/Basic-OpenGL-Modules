#pragma once

// External includes
#include <vector>

// Internal inclues
#include "System.h"

namespace component
{
	/**
	 * This class dispatces the events which came from the diffrent systems.
	 * Since this class just need to be instanciatet once, it is implemented as a Singelton.
	 * When you create a new System you have to add it whith the addSystem function.
	 * When you need a Event processed you have to add the event whith the addEvent function.
	 * And also very importand is that you call the update function in every cycle of the gameloop.
	 * The event stack will be processed in every cycle and deleted as last step in the update function.
	 * @author sascha blank
	 */
	class EventDispatcher
	{
	public:
		/**
		 * Function to get the instance of this class
		 * SINGELTON PATTERN
		 * @author sascha blank
		 */
		static EventDispatcher& Instance();

		/**
		 * virtual destructor
		 */
		virtual ~EventDispatcher( void );

		/**
		 * Add a event to the event stack
		 * @author sascha blank
		 * @param Event* the event pointer which has to be added to the event stack
		 */
		void addEvent(Event* p_event);

		/**
		 * Add a system to the event dispatcher for processing events
		 * @author sascha blank
		 * @param System*, pointer on the system to add
		 */
		void addSystem(System* p_system);

		/**
		 * Update function to process the eventstack
		 * @autho sascha blank
		 */
		void update();

	private:
		
		/**
		 * Private constructor.
		 * SINGELTON PATTERN
		 */
		EventDispatcher( void );

		/**
		 * private copy constructor
		 * @author sascha blank
		 */
		EventDispatcher( const EventDispatcher& t_other ) {}

		// vector with all system which can receive events
		std::vector<System*>m_systems;

		// Eventstack
		std::vector<Event*>m_eventStack;
	};
}
