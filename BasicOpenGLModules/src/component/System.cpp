
// Internal includes
#include "System.h"

using namespace component;

System::System(EnSystem p_system, EntityCollection* p_collection)
{
	m_systemType = p_system;
	m_collection = p_collection;
}


EnSystem System::getSystemType() const
{
	return m_systemType;
}