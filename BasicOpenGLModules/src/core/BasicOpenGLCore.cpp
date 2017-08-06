// External inludes
#include <rapidXml\rapidxml.hpp>
#include <rapidXml\rapidxml_print.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

// Internal includes
#include "BasicOpenGLCore.h"
#include "Display.h"
#include "../component/EventDispatcher.h"

using namespace core;
using namespace component;
using namespace rapidxml;


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


void BasicOpenGLCore::saveSzene( const std::string& p_path )
{
	std::list<Entity*>l_entitys = m_entiyCollection.getAllEntitys();
	xml_document<> l_doc; 
	xml_node<>* l_szeneRootNode = l_doc.allocate_node( node_element, "szene" );
	xml_node<>* l_entitysNode = l_doc.allocate_node( node_element, "entitys" );
	l_doc.append_node( l_szeneRootNode );
	l_szeneRootNode->append_node( l_entitysNode );

	for (auto l_it = l_entitys.begin(); l_it != l_entitys.end(); l_it++)
	{
		( *l_it )->serialize( l_entitysNode );
	}
	std::string xml_as_string;
	print( std::back_inserter( xml_as_string ), l_doc );
	std::ofstream file_stored( p_path.c_str());
	file_stored << l_doc;
	file_stored.close();
	l_doc.clear();
}


void BasicOpenGLCore::loadSzene( const std::string& p_path, const std::string& p_factoryName )
{
	std::string buffer;
	std::string line;
	std::ifstream xml_file( p_path );
	if (xml_file.is_open())
	{
		while (xml_file.good())
		{
			getline( xml_file, line );
			buffer += line;
		}
		xml_file.close();
	}
	else
	{
		std::cout << "ERROR: xml file not found " << p_path << std::endl;
	}

	//Create a char buffer
	char *pbuffer = new char[ buffer.length() + 1 ];
	strcpy_s( pbuffer, sizeof( char )*buffer.length() + 1, buffer.c_str() );
	pbuffer[ buffer.length() ] = '\0';
	xml_document<> doc;
	doc.parse<0>( pbuffer );
	xml_node<>* l_rootNode = doc.first_node( );
	xml_node<>*l_entitysNode = l_rootNode->first_node( "entitys" );
	IComponentFactory* l_factory = m_factorys[ p_factoryName ];
	for (xml_node<>* l_entityNode = l_entitysNode->first_node( "entity" ); l_entityNode; l_entityNode = l_entityNode->next_sibling())
	{
		Entity* l_entity = new Entity( l_entityNode->first_attribute( "name" )->value() );
		for (xml_node<>* l_componentNode = l_entityNode->first_node(); l_componentNode; l_componentNode = l_componentNode->next_sibling())
		{
			l_entity->addComponent( l_factory->generateComponentFromXmlNode( l_componentNode ) );
		}
		m_entiyCollection.addEntity( l_entity );
	}
	doc.clear();
}

