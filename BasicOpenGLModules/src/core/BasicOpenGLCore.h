#pragma once

// External includes
#include <map>
#include <string>

// Internal includes
#include "component\EntityCollection.h"
#include "component\SystemCollection.h"
#include "IComponentFactory.h"
#include "../component/System.h"
#include "ShaderManager.h"

// Protoype class
class Display;

namespace core
{
	/**
	 * This class is the core part of the Libary. 
	 * All system are stored here. 
	 * You can create Entitys with the core class and add an implementation of the IComponentFactory to it.
	 * The factory implementation will be used to create Components for the Entitys.
	 * The order in which the systems are added is the same order as the systems update functions will be called.
	 * @author sascha blank
	 */
	class BasicOpenGLCore
	{
	public:

		/**
		 * Constructor
		 * @author sascha blank
		 * @param Display*, pointer on the display which is used in the application
		 * 
		 */
		BasicOpenGLCore( Display* p_display, ShaderManager* p_shaderManager );
		/**
		 * Virtual destructor
		 */
		virtual ~BasicOpenGLCore();

		/**
		 * Function to add a IComponentFactory Object with a given name
		 * @author sascha blank
		 * @param const std::string& the factory name
		 * @param IComponentFactory* implemented factory object pointer
		 */
		void addComponentFactory( const std::string& p_factoryName, IComponentFactory* t_factory );

		/**
		 * Function to create a new Entity and returns the id of the entity.
		 * You shoud not create Entitys with the new operator!!
		 * @author sascha blank
		 * @param const char* the entity name
		 * @return long the entity ID
		 */
		long createNewEntity( const char* t_objectName);

		/**
		 * Function to add a component to an entity. It uses the factory name picking the IcomponentFactory which you hopefully added in the frist place.
		 * This function will pass the std::vector to the factory so it can use the data for instaciating the component
		 * @author sascha blank
		 * @param long the entity id
		 * @param const std::string& factory name 
		 * @param const std::vector<std::string>& data for the factory
		 */
		void addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::vector<std::string>& p_data );

		/**
		 * Function to add a component to an entity. It uses the factory name picking the IcomponentFactory which you hopefully added in the frist place.
		 * This function will pass the std::map to the factory so it can use the data for instaciating the component
		 * @author sascha blank
		 * @param long the entity id
		 * @param const std::string& factory name
		 * @param const std::map<std::string, std::string>& data for the factory
		 */
		void addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::map<std::string, std::string>& p_data );

		/**
		 * Function to add a component to an entity. It uses the factory name picking the IcomponentFactory which you hopefully added in the frist place.
		 * This function will pass the std::string to the factory so it can use the data for instaciating the component
		 * @author sascha blank
		 * @param long the entity id
		 * @param const std::string& factory name
		 * @param const std::string& data for the factory
		 */
		void addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::string& p_data );

		/**
		 * Function to add a system to the core. 
		 * In the maingameloop the order which you added the system will be the same order as the core is calling the 
		 * Systems update function
		 */
		void addSystem( component::System* p_system );

		/**
		 * Function to start the main loop after the initalization
		 * @author sascha blank
		 */
		void startMainLoop( void);

		/**
		 * Function to stop the main loop when the programm shoud stop
		 * @author sascha blank
		 */
		void stopMainLoop( void );

		/**
		 * Function to return the container with all the Entitys in it
		 * @author sascha blank
		 * @return EntityCollection the collection which holds all the Entitys in it
		 */
		component::EntityCollection& getEntityCollection( void );

	private:

		// Entity Collection 
		component::EntityCollection m_entiyCollection;

		// System collection
		component::SystemCollection m_systemCollection;

		// Start the mainloop
		void runMainLoop();

		// Pointer on the display
		Display* m_display;

		// map with IComponentFactory pointer
		std::map<std::string, IComponentFactory*>m_factorys;

		// is the application running
		bool m_isRunning;

		// Pointer on the shader manager
		ShaderManager* m_shaderManager;
	};
}