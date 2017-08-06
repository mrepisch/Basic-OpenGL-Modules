#pragma once

//External includes
#include <string>

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
		
		/**
		 * Function to serialize the TranslationComponent to xml
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the rootNode
		 */
		void serialize( rapidxml::xml_node<>* p_rootNode );

		/**
		 * Function to read the component data from a xml node
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the component node
		 */
		void deserialize( rapidxml::xml_node<>* p_componentNode );

	private:

		/**
		 * Private copy constructor
		 * @author sascha blank
		 */
		TranslationComponent( const TranslationComponent& t_other );
	};
}