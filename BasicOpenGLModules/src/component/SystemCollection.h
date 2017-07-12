#pragma once

// External includes
#include <vector>

// Internal includes
#include "System.h"


namespace component
{
	class SystemCollection
	{
	public:
		static SystemCollection& Instance();

		virtual ~SystemCollection();

		void addSystem( System* p_system );

		void update();

	private:
		SystemCollection() {}
		SystemCollection( const SystemCollection& t_other ) {}

		std::vector<System*>m_systems;

		
	};
}
