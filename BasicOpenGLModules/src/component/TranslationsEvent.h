#pragma once
#include "Event.h"
#include "../util/Vector3D.h"

namespace component
{
	/**
	 * Event class for the TranslationSystem
	 * This events moves, scales or rotate an Entity
	 * @author sascha blank
	 */
	class TranslationsEvent : public Event
	{
	public:
		/**
		 * Constructor
		 * @author sascha blank
		 * @param long the entity id
		 */
		TranslationsEvent( long p_entityID);

		/**
		 * Virtual destructor
		 * @author sascha blank
		 */
		virtual ~TranslationsEvent();

		// Entity id
		long m_entityID;

		// position offset to add 
		util::VectorF m_positionsOffset;

		// the rotation offset to add
		util::VectorF m_rotationOffset;

		// the scale offset to add
		util::VectorF m_scaleToAdd;
	};
}