#include "EntityCollection.h"


using namespace component;

EntityCollection& EntityCollection::Instance()
{
	static EntityCollection r_collections;
	return r_collections;
}

EntityCollection::EntityCollection()
{

}

EntityCollection::~EntityCollection()
{

}


std::vector<Entity*> EntityCollection::getEntityWithComponents(EnComponents p_component)
{
	std::vector<Entity*>r_entitys;
	for (auto l_iter = m_entitys.begin(); l_iter != m_entitys.end(); l_iter++)
	{
		if ((*l_iter)->getHasComponent(p_component))
		{
			r_entitys.push_back((*l_iter));
		}
	}
	return r_entitys;
}



void EntityCollection::addEntity(Entity* p_entity)
{
	if (p_entity != nullptr)
	{
		m_entitys.push_back(p_entity);
	}
}


Entity* EntityCollection::getEntityByID(long p_id)
{
	Entity* r_entity;
	for (auto l_iter = m_entitys.begin(); l_iter != m_entitys.end(); l_iter++)
	{
		if ((*l_iter)->getEntityID() == p_id)
		{
			r_entity = (*l_iter);
		}
	}
	return r_entity;
}

