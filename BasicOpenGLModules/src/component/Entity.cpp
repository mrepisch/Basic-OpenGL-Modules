
// Internal includes
#include "Entity.h"


using namespace component;
using namespace rapidxml;


long Entity::S_ENTITYCOUNTER = 0;


Entity::Entity(const char* p_objectName)
{
	m_name = p_objectName;
	++S_ENTITYCOUNTER;
	m_entityID = S_ENTITYCOUNTER;
}

Entity::Entity(const Entity& t_other)
{
	*this = t_other;
}

Entity& Entity::operator=(const Entity& t_other)
{
	if(this != &t_other)
	{
		m_components = t_other.m_components;
		m_name = t_other.m_name;
	}
	return *this;
}


const std::string& Entity::getName(void) const
{
	return m_name;
}


bool Entity::getHasComponent(EnComponents p_component)
{
	bool r_hasComponent = false;
	for (auto l_iter = m_components.begin(); l_iter != m_components.end(); l_iter++)
	{
		if ((*l_iter)->getComponentType() == p_component)
		{
			r_hasComponent = true;
			break;
		}
	}
	return r_hasComponent;
}

void Entity::addComponent(Component* p_component)
{
	if (p_component != nullptr)
	{
		m_components.push_back(p_component);
	}
}

long Entity::getEntityID()
{
	return m_entityID;
}

Component* Entity::getComponent(EnComponents p_component)
{
	Component* r_component = nullptr;
	for (auto l_iter = m_components.begin(); l_iter != m_components.end(); l_iter++)
	{
		if ((*l_iter)->getComponentType() == p_component)
		{
			r_component = ( *l_iter );
			break;
		}
	}
	return r_component;
}

void Entity::ResetEntityCounter()
{
	S_ENTITYCOUNTER = 0;
}


void Entity::serialize( xml_node<>* p_rootNode )
{
	xml_document<>* l_doc = p_rootNode->document();
	xml_node<>*l_entityNode = l_doc->allocate_node( node_element, "entity" );
	l_entityNode->append_attribute( l_doc->allocate_attribute( "name", m_name.c_str() ) );
	p_rootNode->append_node( l_entityNode );
	for (auto l_iter = m_components.begin(); l_iter != m_components.end(); l_iter++)
	{
		( *l_iter )->serialize( l_entityNode );
	}
}