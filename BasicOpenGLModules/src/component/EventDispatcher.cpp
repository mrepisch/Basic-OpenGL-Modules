
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

void EventDispatcher::addSystem(EnEventType p_eventType, System* p_system)
{
	if (p_system != nullptr)
	{
		m_systemMap.insert(std::make_pair(p_eventType, p_system));
	}
}

void EventDispatcher::update()
{
	for (auto l_stackIter = m_eventStack.begin(); l_stackIter != m_eventStack.end(); l_stackIter++)
	{
		EnEventType l_eventType = (*l_stackIter)->getEventType();
		if (m_systemMap.find(l_eventType) != m_systemMap.end())
		{
			m_systemMap[l_eventType]->receiveMessage((*l_stackIter));
		}
	}
}