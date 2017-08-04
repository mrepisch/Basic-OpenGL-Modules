
//Internal includes
#include "TranslationComponent.h"


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
	xml_node<>* l_translationNode = l_doc->allocate_node( node_element, "position" );
	l_translationNode->append_attribute( l_doc->allocate_attribute( "x", std::to_string( ( double )m_position.getX() ).c_str() ) );
	l_translationNode->append_attribute( l_doc->allocate_attribute( "y", std::to_string( ( double )m_position.getY() ).c_str() ) );
	l_translationNode->append_attribute( l_doc->allocate_attribute( "z", std::to_string( ( double )m_position.getZ() ).c_str() ) );
	l_componentNode->append_node( l_translationNode );
	xml_node<>* l_rotationNode = l_doc->allocate_node( node_element, "rotation" );
	l_rotationNode->append_attribute( l_doc->allocate_attribute( "x", std::to_string( ( double )m_rotation.getX() ).c_str() ) );
	l_rotationNode->append_attribute( l_doc->allocate_attribute( "y", std::to_string( ( double )m_rotation.getY() ).c_str() ) );
	l_rotationNode->append_attribute( l_doc->allocate_attribute( "z", std::to_string( ( double )m_rotation.getZ() ).c_str() ) );
	l_componentNode->append_node( l_rotationNode );

	xml_node<>* l_scaleNode = l_doc->allocate_node( node_element, "scale" );
	l_scaleNode->append_attribute( l_doc->allocate_attribute( "x", std::to_string( ( double )m_scale.getX() ).c_str() ) );
	l_scaleNode->append_attribute( l_doc->allocate_attribute( "y", std::to_string( ( double )m_scale.getY() ).c_str() ) );
	l_scaleNode->append_attribute( l_doc->allocate_attribute( "z", std::to_string( ( double )m_scale.getZ() ).c_str() ) );
	l_componentNode->append_node( l_scaleNode );

	p_rootNode->append_node( l_componentNode );

}