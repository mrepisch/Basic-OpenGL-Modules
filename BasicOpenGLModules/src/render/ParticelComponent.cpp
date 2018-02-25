
// Internal includes
#include "ParticelComponent.h"
#include "../util/Util.h"

using namespace render;
using namespace component;
using namespace util;
using namespace rapidxml;

ParticelComponent::ParticelComponent() : Component(e_particelComponent)
{

}

ParticelComponent::~ParticelComponent()
{

}

void ParticelComponent::serialize( rapidxml::xml_node<>* p_rootNode )
{
	xml_document<>* l_doc = p_rootNode->document();
	xml_node<>* l_particelComponentNode = l_doc->allocate_node( node_element, "particleComponent" );
	p_rootNode->append_node( l_particelComponentNode );
	
	xml_node<>* l_durationNode = l_doc->allocate_node(node_element, "duratation" );
	l_particelComponentNode->append_node( l_durationNode );
	Util::writeFloatAsAttributeToXmlNode( m_durotation, "float", l_durationNode );
	
	xml_node<>* l_particleCountNode = l_doc->allocate_node(node_element, "particleCount" );
	l_particelComponentNode->append_node( l_particleCountNode );
	Util::writeFloatAsAttributeToXmlNode( ( float )particleCount, "int", l_particelComponentNode );

	xml_node<>* l_particleScale = l_doc->allocate_node( node_element, "particleScale" );
	l_particelComponentNode->append_node( l_particleScale );
	Util::writeFloatAsAttributeToXmlNode( particleScale, "float", l_particelComponentNode );

	Util::writeVectorToXmlNode( m_particleColor, "color", l_particelComponentNode );

	xml_node<>*l_texturesNode = l_doc->allocate_node( node_element,"textures" );
	l_particelComponentNode->append_node( l_texturesNode );
	for (auto a_it : texturesMap)
	{
		xml_node<>* l_textureNode = l_doc->allocate_node( node_element, "texture" );
		l_texturesNode->append_attribute( l_doc->allocate_attribute( "path", a_it.second->getTexturePath() ) );
		l_texturesNode->append_node( l_textureNode );
	}

}

void ParticelComponent::deserialize( rapidxml::xml_node<>* p_componentNode )
{

}