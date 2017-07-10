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

	/**
	 * Baseclass of all Systems.
	 * To inherit from this class you need to implement the update Function 
	 * and the constructor.
	 * And also you need to add a new entry in the enum.
	 * In general each System use one Componenttype.
	 * @author sascha blank
	 */
	class System
	{
	public:

		/**
		 * Constructor
		 * @author sascha blank
		 * @param p_system, Enum entry of the system
		 */
		System(EnSystem p_system);

		/**
		 * Returns the SystemtType enum definition of the system
		 * @author sascha blank
		 * @return EnSystem
		 */
		EnSystem getSystemType() const;

		/**
		 * Function to implement in the inherited system
		 * @author sascha blank
		 */
		virtual void update() = 0;

	protected:

		// The Sytem type definition
		EnSystem m_systemType;

		// The entity collection
		EntityCollection* m_entityCollection;
	};
}