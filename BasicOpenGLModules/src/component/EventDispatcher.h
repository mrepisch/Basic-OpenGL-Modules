#pragma once

// External includes
#include <map>
#include <vector>
#include "System.h"

// forward decleration


namespace component
{
	class EventDispatcher
	{
	public:
		static EventDispatcher& Instance();

		void addEvent(Event* p_event);

		void addSystem(System* p_system);

		void update();

	private:
		EventDispatcher();
		std::vector<System*>m_systems;

		std::vector<Event*>m_eventStack;
	};
}
