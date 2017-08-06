// Internal includes
#include "RenderComponent.h"
#include "../util/BGLMeshLoader.h"

using namespace render;
using namespace component;
using namespace rapidxml;


RenderComponent::RenderComponent( render::Mesh* p_mesh ) : Component(e_renderComponent)
{
	m_mesh = p_mesh;
}

RenderComponent::RenderComponent() : Component( e_renderComponent)
{
	m_mesh = nullptr;
}


RenderComponent::~RenderComponent( void )
{
	delete m_mesh;
}


void RenderComponent::serialize( rapidxml::xml_node<>* p_rootNode )
{
	xml_document<>* l_doc = p_rootNode->document();
	xml_node<>*l_renderComponentNode = l_doc->allocate_node( node_element, "renderComponent" );
	p_rootNode->append_node( l_renderComponentNode );
	xml_node<>*l_meshFileNode = l_doc->allocate_node( node_element, "meshFile" );
	l_meshFileNode->append_attribute( l_doc->allocate_attribute( "path", m_meshFileName.c_str() ) );
	l_renderComponentNode->append_node( l_meshFileNode );

	xml_node<>*l_shaderName = l_doc->allocate_node( node_element, "shaderName" );
	l_shaderName->append_attribute( l_doc->allocate_attribute( "string", m_mesh->getShaderProgramNameName().c_str() ) );
	l_renderComponentNode->append_node( l_shaderName );
}


void RenderComponent::deserialize( rapidxml::xml_node<>* p_node )
{
	std::string l_meshFile = p_node->first_node( "meshFile" )->first_attribute("path")->value();
	util::BGLMeshLoader l_loader;
	m_mesh = l_loader.loadMesh( l_meshFile );
	m_mesh->generateBuffer();
	m_meshFileName = l_meshFile;
	m_mesh->setShaderProgramName( p_node->first_node( "shaderName" )->first_attribute( "string" )->value() );
}