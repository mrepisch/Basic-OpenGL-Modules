
// Internal include
#include "EventDispatcher.h"
#include "System.h"
#include "Event.h"
using namespace component;


EventDispatcher& EventDispatcher::Instance()
{
	static EventDispatcher r_instance;
	return r_instance;
}

EventDispatcher::EventDispatcher()
{

}

void EventDispatcher::addEvent(Event* p_event)
{
	m_eventStack.push_back(p_event);
}

void EventDispatcher::addSystem(System* p_system)
{
	if (p_system != nullptr)
	{
		m_systems.push_back( p_system);
	}
}

void EventDispatcher::update()
{
	for (int i = 0; i < m_eventStack.size(); ++i)
	{
		for (auto l_systemIter = m_systems.begin(); l_systemIter != m_systems.end(); l_systemIter++)
		{
			( *l_systemIter )->receiveEvent( m_eventStack[i] );
		}
	}
	m_eventStack.clear();
	
}