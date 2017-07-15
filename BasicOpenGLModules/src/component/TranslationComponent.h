#pragma once

// Internal includes
#include "Component.h"
#include "util\Vector3D.h"

namespace component
{
	/**
	 * This class is the Translation component. 
	 * It contains the position, rotation and scale of an entity.
	 * It is used for manipulatin the Entitys position, rotation and scale
	 * @author sascha blank
	 */
	class TranslationComponent : public Component
	{
	public:

		/**
		 * Default constructor
		 * @author sascha blank
		 */
		TranslationComponent( void );

		// Position vector
		util::VectorF m_position;

		// Rotation vector
		util::VectorF m_rotation;

		// Scale vector
		util::VectorF m_scale;

	private:

		/**
		 * Private copy constructor
		 * @author sascha blank
		 */
		TranslationComponent( const TranslationComponent& t_other );
	};
}