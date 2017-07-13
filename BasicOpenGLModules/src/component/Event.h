#pragma once

namespace component 
{
	enum EnEventType
	{
		e_undefinedEvent = 0,
		e_translationEvent,
		e_renderEvent,
		e_cameraEvent
	};

	class Event
	{
	public:
		Event( EnEventType p_eventType );

		EnEventType getEventType();

	protected:

		EnEventType m_eventType;
	};

}