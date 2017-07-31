#include "CameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace game;
using namespace component;

CameraComponent::CameraComponent( int p_screenWidth, int p_screenHeight, float p_depth ) : Component( e_cameraComponent )
{
	m_screenHeight = p_screenHeight;
	m_screenWidth = p_screenWidth;
	m_depth = p_depth;
	m_aspectRatio =(float) m_screenWidth / m_screenHeight;

	m_pos[ 0 ] = 0.0f;
	m_pos[ 1 ] = 1.0f;
	m_pos[ 2 ] = 0.0f;

	m_cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
	m_cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );
}

glm::mat4 CameraComponent::getViewMatrix( void )
{
	return glm::lookAt( m_pos, m_pos + m_cameraFront, m_cameraUp );
}