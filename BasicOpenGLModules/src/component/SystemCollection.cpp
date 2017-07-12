#include "SystemCollection.h"

using namespace component;


SystemCollection& SystemCollection::Instance()
{
	static SystemCollection r_instance;
	return r_instance;
}


SystemCollection::~SystemCollection()
{
	for (int i = 0; i < m_systems.size(); ++i)
	{
		delete m_systems[ i ];
	}
	m_systems.clear();
}

void SystemCollection::addSystem( System* p_system )
{
	if (p_system != nullptr)
	{
		m_systems.push_back( p_system );
	}
}


void SystemCollection::update()
{
	for (int i = 0; i < m_systems.size(); ++i)
	{
		m_systems[ i ]->update();
	}
}