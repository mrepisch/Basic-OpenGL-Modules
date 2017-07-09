#pragma once

// External includes
#include <string>
#include <list>

// Internal includes
#include "Component.h"


namespace component
{
	class Entity
	{
	public:
		Entity( const char* p_objectName);
		Entity(const Entity& t_other);
		Entity& operator=(const Entity& t_other);

		const std::string& getName(void) const;

		bool getHasComponent(EnComponents p_component);

		void update(void);
		void render(void);

		long getEntityID();

	private:

		static long S_ENTITYCOUNTER;
		
		std::string m_name;
		long m_entityID;
		std::list<Component*>m_components;
	};
}