#pragma once

// External includes
#include <map>
#include <list>
#include "System.h"
// forward decleration


namespace component
{
	class MessageDispatcher
	{
	public:
		static MessageDispatcher& Instance();

		void addEvent(Event* p_event);

		void addSystem(EnEventType p_eventType, System* p_system);

		void update();

	private:
		MessageDispatcher();

		std::map<EnEventType, System*>m_systemMap;
		std::map<EnEventType, System*>::iterator m_systemMapIterator;

		std::list<Event*>m_eventStack;
	};
}
