#pragma once

// External includes
#include <list>
#include <vector>

// Internal includes
#include "Entity.h"

namespace component
{
	class EntityCollection
	{
	public:
		static EntityCollection& Instance();
		virtual ~EntityCollection();
		std::vector<Entity*>getEntityWithComponents(EnComponents p_component);
		Entity* getEntityByID(long p_id);
		void addEntity(Entity* p_entity);

	private:
		std::list<Entity*>m_entitys;
		EntityCollection();
	};
}