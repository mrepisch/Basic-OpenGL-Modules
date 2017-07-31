#pragma once
#include <map>
#include <string>

#include "component\EntityCollection.h"
#include "component\SystemCollection.h"
#include "IComponentFactory.h"
#include "../component/System.h"
#include "ShaderManager.h"
class Display;



namespace core
{



	class BasicOpenGLCore
	{
	public:
		BasicOpenGLCore( Display* p_display, ShaderManager* p_shaderManager );
		virtual ~BasicOpenGLCore();

		

		void addComponentFactory( const std::string& p_factoryName, IComponentFactory* t_factory );

		long createNewEntity( const char* t_objectName);

		void addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::vector<std::string>& p_data );
		void addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::map<std::string, std::string>& p_data );
		void addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::string& p_data );

		void addSystem( component::System* p_system );

		

		void startMainLoop( void);

		void stopMainLoop( void );

		component::EntityCollection& getEntityCollection( void );



	private:
		component::EntityCollection m_entiyCollection;
		component::SystemCollection m_systemCollection;

		void runMainLoop();

		Display* m_display;

		std::map<std::string, IComponentFactory*>m_factorys;

		bool m_isRunning;

		ShaderManager* m_shaderManager;

	};
}