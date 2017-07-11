
// Internal include
#include "MessageDispatcher.h"
#include "System.h"
#include "Event.h"
using namespace component;


MessageDispatcher& MessageDispatcher::Instance()
{
	static MessageDispatcher r_instance;
	return r_instance;
}

MessageDispatcher::MessageDispatcher()
{

}

void MessageDispatcher::addEvent(Event* p_event)
{
	m_eventStack.push_back(p_event);
}

void MessageDispatcher::addSystem(EnEventType p_eventType, System* p_system)
{
	if (p_system != nullptr)
	{
		m_systemMap.insert(std::make_pair(p_eventType, p_system));
	}
}

void MessageDispatcher::update()
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