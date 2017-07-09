#pragma once

// Internal includes
#include "EntityCollection.h"

namespace component
{
	enum EnSystem
	{
		e_undefinedSystem = 0,
		e_renderSystem,
		e_cameraSystem
	};

	class System
	{
	public:
		System(EnSystem p_system);

		EnSystem getSystemID() const;

		virtual void update() = 0;

	protected:
		EnSystem m_systemID;
		EntityCollection* m_entityCollection;
	};
}