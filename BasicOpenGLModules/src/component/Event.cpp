
// Internal includes
#include "Event.h"

using namespace component;


Event::Event(EnEventType p_eventType)
{
	m_eventType = p_eventType;
}


EnEventType Event::getEventType()
{
	return m_eventType;
}