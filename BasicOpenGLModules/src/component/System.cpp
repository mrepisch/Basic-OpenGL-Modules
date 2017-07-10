
// Internal includes
#include "System.h"

using namespace component;

System::System(EnSystem p_system)
{
	m_systemType = p_system;
	m_entityCollection = &EntityCollection::Instance();
}


EnSystem System::getSystemType() const
{
	return m_systemType;
}