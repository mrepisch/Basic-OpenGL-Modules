#pragma once

// External includes
#include <string>
#include <list>
#include <rapidXml\rapidxml.hpp>
// Internal includes
#include "Component.h"
 
namespace component
{
	/**
	 * This class represents the entity in the scene.
	 * It holds a list of components.
	 * Steps to use the Entity Class.
	 * 1) Create a new Entity and give it a name
	 * 2) Use the addComponent function to add components 
	 * 3) Add the Entity to the Instance of EntityCollection.
	 * 4) The System implementation will use the Entitys and its components.
	 * 5) The Entity class will delete all components in its destructor
	 * !IMPORTANT just one ComponentType per Entity(f.e not 2 Render component)
	 */
	class Entity
	{
	public:
		
		/**
		 * Constructor.
		 * @author sascha blank
		 * @param p_objectName
		 */
		Entity( const char* p_objectName);

		/**
		 * Copy Constructor
		 * @author sascha blank
		 * @param t_other, the object to copy
		 */
		Entity( const Entity& t_other);

		/**
		 * Assingment operator
		 * @author sascha blank
		 * @param t_other the object to assing
		 */
		Entity& operator=(const Entity& t_other);

		/**
		 * Function to return the Entityname
		 * @author sascha blank
		 * @return std::strin with the Entityname
		 */
		const std::string& getName(void) const;

		/**
		 * Function to add a Component to the Entity.
		 * Make sure you just add one Componenttype per example
		 * @author sascha blank
		 * @param Component*, pointer on a component
		 */
		void addComponent(Component* p_component);

		/**
		 * Function to return if the Entity holds an Component 
		 * with the given enum.
		 * @author sbl
		 * @param EnComponents the EnComponents enum 
		 * @return bool true if the Entity contains this Component, false otherwise
		 */
		bool getHasComponent(EnComponents p_component);

		/**
		 * Function to return an Component pointer with the given enum 
		 * @author sascha blank
		 * @param EnComponents enum tpye of the component
		 */
		Component* getComponent(EnComponents p_component);

		/**
		 * Returns the Entity ID
		 * @author sascha blank
		 * @return long, with the entityID.
		 */
		long getEntityID();

		/**
		 * Resets the static S_ENTITYCOUNTER to 0
		 * Call this function when you load a new scene
		 * @author sascha blank
		 */
		static void ResetEntityCounter( void );

		/**
		 * Function write the Entity as xml_node<>* 
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the node to add the Entity node to.
		 */
		void serialize( rapidxml::xml_node<>* p_rootNode );

	private:

		// Static Entity Counter
		static long S_ENTITYCOUNTER;
		
		// The name of the Entity
		std::string m_name;
		
		// List with all the components of the Entity
		std::list<Component*>m_components;

		// The EntityID of the Entity
		long m_entityID;
	};
}