
//Internal includes
#include "TranslationComponent.h"
#include "../util/Util.h"

using namespace component;
using namespace rapidxml;


TranslationComponent::TranslationComponent(void) :Component(e_translationComponent)
{
	m_position.set(0.0f, 0.0f, 0.0f);
	m_scale.set(1.0f, 1.0f, 1.0f);
	m_rotation.set(0.0f, 0.0f, 0.0f);
}


void TranslationComponent::serialize( rapidxml::xml_node<>* p_rootNode )
{
	
	xml_document<> *l_doc = p_rootNode->document();
	xml_node<>* l_componentNode = l_doc->allocate_node( node_element, "translationComponent" );
	p_rootNode->append_node( l_componentNode );

	util::Util::writeVectorToXmlNode( m_position, "position", l_componentNode );
	util::Util::writeVectorToXmlNode( m_scale, "scale", l_componentNode );
	util::Util::writeVectorToXmlNode( m_rotation, "rotation", l_componentNode );
}


void TranslationComponent::deserialize( rapidxml::xml_node<>* p_componentNode )
{
	m_position = util::Util::readVectorFromXmlNode( p_componentNode->first_node( "position" ) );
	m_scale = util::Util::readVectorFromXmlNode( p_componentNode->first_node( "scale" ) );
	m_rotation = util::Util::readVectorFromXmlNode( p_componentNode->first_node( "rotation" ) );
}