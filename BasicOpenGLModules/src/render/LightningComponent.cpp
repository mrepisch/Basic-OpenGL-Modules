
// Internal includes
#include "LightningComponent.h"
#include "../util/Util.h"


using namespace render;
using namespace component;
using namespace rapidxml;
using namespace util;

LightningComponent::LightningComponent( EnLightType p_type, const std::string& p_shaderName ) : Component( e_lightningComponent )
{
	m_type = p_type;
	m_lightColor.set( 0.75f, 0.75f,0.75f );
	m_ambient.set( 0.0f, 0.0f, 0.0f );
	m_direction.set( 0.0f,0.0f,0.0f);
	m_position.set( 0.0f, 0.0f, 0.0f );
	m_specular.set( 0.0f, 0.0f, 0.0f );
	m_diffuse.set( 0.0f, 0.0f, 0.0f );
	m_constant = 1.0f;
	m_linear = 0.05f;
	m_quadratic = 0.012f;
	m_cutOff = 0.2f;
	m_outCutOff = 0.8f;
	m_shaderName = p_shaderName;
}

LightningComponent::~LightningComponent()
{

}


void LightningComponent::serialize( xml_node<>* p_rootNode )
{
	xml_document<>* l_doc = p_rootNode->document();
	xml_node<>* l_lightComponentNode = l_doc->allocate_node( node_element, "lightComponent" );
	p_rootNode->append_node( l_lightComponentNode );
	Util::writeFloatAsAttributeToXmlNode( m_type, "type", l_lightComponentNode );
	Util::writeVectorToXmlNode( m_lightColor, "lightColor", l_lightComponentNode );
	Util::writeVectorToXmlNode( m_ambient, "ambient", l_lightComponentNode );
	Util::writeVectorToXmlNode( m_position, "position", l_lightComponentNode );
	Util::writeVectorToXmlNode( m_specular, "specular", l_lightComponentNode );
	Util::writeVectorToXmlNode( m_diffuse, "diffuse", l_lightComponentNode );
	
	xml_node<>* l_constantNode = l_doc->allocate_node( node_element, "constant" );
	l_lightComponentNode->append_node( l_constantNode );
	Util::writeFloatAsAttributeToXmlNode( m_constant, "float", l_constantNode );
	
	xml_node<>* l_linearNode = l_doc->allocate_node( node_element, "linear" );
	l_lightComponentNode->append_node( l_linearNode );
	Util::writeFloatAsAttributeToXmlNode( m_linear, "float", l_linearNode );
	
	xml_node<>*l_quadraticNode = l_doc->allocate_node( node_element, "quadratic" );
	l_lightComponentNode->append_node( l_quadraticNode );
	Util::writeFloatAsAttributeToXmlNode( m_quadratic, "float", l_quadraticNode );

	xml_node<>*l_cutoffNode = l_doc->allocate_node( node_element, "cutoff" );
	l_lightComponentNode->append_node( l_cutoffNode );
	Util::writeFloatAsAttributeToXmlNode( m_cutOff, "float", l_cutoffNode );
	
	xml_node<>*l_outCutOffNode = l_doc->allocate_node( node_element, "outCutOff" );
	l_lightComponentNode->append_node( l_outCutOffNode );
	Util::writeFloatAsAttributeToXmlNode( m_outCutOff, "float", l_outCutOffNode );

	xml_node<>* l_shaderNameNode = l_doc->allocate_node( node_element, "shadername" );
	l_shaderNameNode->append_attribute( l_doc->allocate_attribute( "string", m_shaderName.c_str() ) );
}

void LightningComponent::deserialize( rapidxml::xml_node<>* p_node )
{
	m_type = (EnLightType)(( int )std::stof( p_node->first_attribute( "type" )->value() ));
	m_lightColor = Util::readVectorFromXmlNode( p_node->first_node( "lightColor" ) );
	m_ambient = Util::readVectorFromXmlNode( p_node->first_node( "ambient" ) );
	m_position = Util::readVectorFromXmlNode( p_node->first_node( "postition" ) );
	m_specular = Util::readVectorFromXmlNode( p_node->first_node( "specular" ) );
	m_diffuse = Util::readVectorFromXmlNode( p_node->first_node( "diffuse" ) );
	m_constant = Util::readFloatFromAttribute( p_node->first_node( "constant" ), "float" );
	m_linear = Util::readFloatFromAttribute( p_node->first_node( "linear" ), "float" );
	m_quadratic = Util::readFloatFromAttribute( p_node->first_node( "quadratic" ), "float" );
	m_cutOff = Util::readFloatFromAttribute( p_node->first_node( "cutoff"), "float" );
	m_outCutOff = Util::readFloatFromAttribute( p_node->first_node( "outCutOff" ), "float" );
	m_shaderName = p_node->first_node( "shadername" )->first_attribute( "string" )->value();
}