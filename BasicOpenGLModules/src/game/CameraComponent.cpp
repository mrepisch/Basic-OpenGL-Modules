// External includes
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Internal includes
#include "CameraComponent.h"
#include "../util/Util.h"

using namespace game;
using namespace component;
using namespace rapidxml;
using namespace util;

CameraComponent::CameraComponent( int p_screenWidth, int p_screenHeight, float p_depth, bool p_isActive ) : Component( e_cameraComponent )
{
	m_screenHeight = p_screenHeight;
	m_screenWidth = p_screenWidth;
	m_depth = p_depth;
	m_aspectRatio =(float) m_screenWidth / m_screenHeight;

	m_pos[ 0 ] = 0.0f;
	m_pos[ 1 ] = 1.0f;
	m_pos[ 2 ] = 0.0f;

	m_front = glm::vec3( 0.0f, 0.0f, -1.0f );
	m_up = glm::vec3( 0.0f, 1.0f, 0.0f );
	m_worldUp = glm::vec3( 0.0f, 1.0f, 0.0f );
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	m_isActiveCamera = p_isActive;
}

glm::mat4 CameraComponent::getViewMatrix( void )
{
	return glm::lookAt( m_pos, m_pos + m_front, m_up );
}


void CameraComponent::serialize( rapidxml::xml_node<>* p_rootNode )
{
	xml_document<>* l_doc = p_rootNode->document();
	xml_node<>* l_cameraComponentNode = l_doc->allocate_node( node_element, "cameraComponent" );
	p_rootNode->append_node( l_cameraComponentNode );
	Util::writeGLMVectorToXmlNode( m_pos, "position", l_cameraComponentNode );
	Util::writeGLMVectorToXmlNode( m_front, "front", l_cameraComponentNode );
	Util::writeGLMVectorToXmlNode( m_up, "up", l_cameraComponentNode );
	Util::writeGLMVectorToXmlNode( m_worldUp, "worldup", l_cameraComponentNode );
	xml_node<>* l_pitchNode = l_doc->allocate_node( node_element, "pitch" );
	l_cameraComponentNode->append_node( l_pitchNode );
	Util::writeFloatAsAttributeToXmlNode( m_pitch, "float", l_pitchNode );
	
	xml_node<>* l_yawNode = l_doc->allocate_node( node_element, "yaw" );
	l_cameraComponentNode->append_node( l_yawNode );
	Util::writeFloatAsAttributeToXmlNode( m_yaw, "float", l_yawNode );
	
	xml_node<>*l_isActiveNode = l_doc->allocate_node( node_element, "isActive" );
	if (m_isActiveCamera)
	{
		l_isActiveNode->append_attribute( l_doc->allocate_attribute( "bool", "true" ) );
	}
	else
	{
		l_isActiveNode->append_attribute( l_doc->allocate_attribute( "bool", "false" ) );
	}
	l_cameraComponentNode->append_node( l_isActiveNode );

}

void CameraComponent::deserialize( xml_node<>* p_node )
{
	m_pos = Util::readGLMVectorFromXmlNode( p_node->first_node("position") );
	m_front = Util::readGLMVectorFromXmlNode( p_node->first_node( "front" ) );
	m_up = Util::readGLMVectorFromXmlNode( p_node->first_node( "up" ) );
	m_worldUp = Util::readGLMVectorFromXmlNode( p_node->first_node( "worldup" ) );
	m_pitch = Util::readFloatFromAttribute( p_node->first_node( "pitch" ), "float" );
	m_yaw = Util::readFloatFromAttribute( p_node->first_node( "yaw" ), "float" );
	std::string isActive = p_node->first_node( "isActive" )->first_attribute( "bool" )->value();
	if (isActive == "true")
	{
		m_isActiveCamera = true;
	}
	else
	{
		m_isActiveCamera = false;
	}
}