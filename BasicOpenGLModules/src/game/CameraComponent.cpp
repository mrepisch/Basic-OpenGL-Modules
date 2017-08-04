#include "CameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace game;
using namespace component;

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

}