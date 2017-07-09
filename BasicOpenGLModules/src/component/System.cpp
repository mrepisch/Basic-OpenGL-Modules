
// Internal includes
#include "System.h"

using namespace component;

System::System(EnSystem p_system)
{
	m_systemID = p_system;
	m_entityCollection = &EntityCollection::Instance();
}


EnSystem System::getSystemID() const
{
	return m_systemID;
}