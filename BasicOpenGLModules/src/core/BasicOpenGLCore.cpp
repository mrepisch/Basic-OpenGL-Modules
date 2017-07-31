#include "BasicOpenGLCore.h"
#include "Display.h"
#include "../component/EventDispatcher.h"

using namespace core;
using namespace component;

BasicOpenGLCore::BasicOpenGLCore( Display* p_display, ShaderManager* p_shaderManager )
{
	m_shaderManager = p_shaderManager;
	m_display = p_display;
	m_isRunning = true;
}

BasicOpenGLCore::~BasicOpenGLCore()
{
	
}


void BasicOpenGLCore::addComponentFactory( const std::string& p_factoryName, IComponentFactory* t_factory )
{
	if (t_factory != nullptr)
	{
		m_factorys.insert( std::make_pair( p_factoryName, t_factory ) );
	}
}

void BasicOpenGLCore::startMainLoop()
{
	m_isRunning = true;
	runMainLoop();
}

void BasicOpenGLCore::stopMainLoop()
{
	m_isRunning = false;
}


void BasicOpenGLCore::addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::vector<std::string>& p_data )
{
	if (m_factorys.find( t_factoryName ) != m_factorys.end())
	{
		Component* l_component = m_factorys[ t_factoryName ]->generateComponentFromVector( p_data );
		Entity* l_entity = m_entiyCollection.getEntityByID( p_entityID );
		if (l_entity != nullptr)
		{
			l_entity->addComponent( l_component );
		}
	}
}

void BasicOpenGLCore::addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::map<std::string, std::string>& p_data )
{
	if (m_factorys.find( t_factoryName ) != m_factorys.end())
	{
		Component* l_component = m_factorys[ t_factoryName ]->generateComponentFromMap( p_data );
		Entity* l_entity = m_entiyCollection.getEntityByID( p_entityID );
		if (l_entity != nullptr)
		{
			l_entity->addComponent( l_component );
		}
	}
}

void BasicOpenGLCore::addComponentToEntity( long p_entityID, const std::string& t_factoryName, const std::string& p_data )
{
	if (m_factorys.find( t_factoryName ) != m_factorys.end())
	{
		Component* l_component = m_factorys[ t_factoryName ]->generateComponentFromString( p_data );
		Entity* l_entity = m_entiyCollection.getEntityByID( p_entityID );
		if (l_entity != nullptr)
		{
			l_entity->addComponent( l_component );
		}
	}
}


void BasicOpenGLCore::addSystem( System* p_system )
{
	if (p_system != nullptr)
	{
		m_systemCollection.addSystem( p_system );
		EventDispatcher::Instance().addSystem( p_system );
	}
}



void BasicOpenGLCore::runMainLoop()
{
	while (m_isRunning)
	{
		m_display->clearScreen();
		EventDispatcher::Instance().update();
		m_systemCollection.update();
		m_display->swap();
		if (m_display->getIsClosed())
		{
			m_isRunning = false;
		}
	}
}


EntityCollection& BasicOpenGLCore::getEntityCollection()
{
	return m_entiyCollection;
}


long BasicOpenGLCore::createNewEntity( const char* t_objectName )
{
	long r_entityID = -1;
	Entity* l_entity = new Entity( t_objectName );
	r_entityID = l_entity->getEntityID();
	m_entiyCollection.addEntity( l_entity );
	return r_entityID;
}