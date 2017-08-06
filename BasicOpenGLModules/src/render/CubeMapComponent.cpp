#include "CubeMapComponent.h"
#include <glew\GL\glew.h>

using namespace render;
using namespace component;
using namespace rapidxml;


CubeMapComponent::CubeMapComponent() :Component( e_cubemapComponent )
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	// skybox VAO

	glGenVertexArrays( 1, &skyboxVAO );
	glGenBuffers( 1, &skyboxVBO );
	glBindVertexArray( skyboxVAO );
	glBindBuffer( GL_ARRAY_BUFFER, skyboxVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( skyboxVertices ), &skyboxVertices, GL_STATIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );
}


CubeMapComponent::~CubeMapComponent()
{
	glDeleteVertexArrays( 1, &skyboxVAO );
}


void CubeMapComponent::serialize( xml_node<>* p_rootNode )
{
	xml_document<>* l_doc = p_rootNode->document();
	xml_node<>* l_cubemapComponentNode = l_doc->allocate_node( node_element, "cubemapComponent" );
	std::vector<std::string>texturepaths = m_texture->getTexturePaths();
	for (int i = 0; i < texturepaths.size(); ++i)
	{
		xml_node<>*l_texturenode = l_doc->allocate_node( node_element, "texture" );
		std::string* l_path = new std::string( texturepaths[ i ] );
		l_texturenode->append_attribute( l_doc->allocate_attribute( "path", l_path->c_str() ) );
		l_cubemapComponentNode->append_node( l_texturenode );
	}
	xml_node<>* l_shaderNameNode = l_doc->allocate_node( node_element, "shaderName" );
	l_shaderNameNode->append_attribute( l_doc->allocate_attribute( "string" , m_shaderName.c_str() ) );
	l_cubemapComponentNode->append_node( l_shaderNameNode );
	p_rootNode->append_node( l_cubemapComponentNode );
}


void CubeMapComponent::deserialize( xml_node<>* p_node )
{
	std::vector<std::string>l_paths;
	for (xml_node<>* l_textureNode = p_node->first_node( "texture" ); l_textureNode; l_textureNode = l_textureNode->next_sibling())
	{
		if( std::string(l_textureNode->name()) == "texture")
		{
			std::string l_pathStr = l_textureNode->first_attribute( "path" )->value();
			l_paths.push_back( l_pathStr );
		}
	}
	m_shaderName = p_node->first_node( "shaderName" )->first_attribute( "string" )->value();
	

	m_texture = new CubeMapTexture( l_paths );
}