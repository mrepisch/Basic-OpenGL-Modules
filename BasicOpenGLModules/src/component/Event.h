#pragma once

namespace component 
{
	enum EnEventType
	{
		e_undefinedEvent = 0,
		e_translationEvent,
		e_renderEvent,
		e_cameraEvent,
		e_lightEvent
	};

	/**
	 * Event baseclass for the Systems.
	 * Every system has his own events and components.
	 * The System class contains the processEvent function which takes an implementation of an Event.
	 * For implementing a new Event you have to add a new entry in the enum above.
	 * @author sascha blank
	 */
	class Event
	{
	public:
		/**
		 * Constructor
		 * @author sascha blank
		 * @param EnEventType, the eventtype which this event is
		 */
		Event( EnEventType p_eventType );

		/**
		 * Function to return the eventtype
		 * @author sascha blank
		 * @return EnEventType 
		 */
		EnEventType getEventType();

	protected:

		// The event type which is unses in this event
		EnEventType m_eventType;
	};

}