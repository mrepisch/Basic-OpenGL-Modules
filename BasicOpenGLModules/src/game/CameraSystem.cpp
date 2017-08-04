
//External inlcudes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

// Internal includes
#include "CameraSystem.h"
#include "..\game\CameraEvent.h"
#include "..\component\EntityCollection.h"



const float YAW = -90.0f;
const float PITCH = 0.0f;

using namespace component;
using namespace game;

CameraSystem::CameraSystem( EntityCollection* p_collection ) : System( e_cameraSystem, p_collection )
{
	
}


CameraSystem::~CameraSystem()
{

}


void CameraSystem::update()
{
	/*std::vector<Entity*>l_cameras = m_collection->getEntityWithComponents( e_cameraComponent );
	if (l_cameras.size() > 0)
	{
		Entity* l_camera = l_cameras[ 0 ];
		if (l_camera != nullptr)
		{
			CameraComponent* a_comp =(CameraComponent*)( l_camera->getComponent( e_cameraComponent ) );
			if (a_comp != nullptr)
			{


			}
		}
	}*/
}


void CameraSystem::receiveEvent( Event* p_event )
{
	if (p_event->getEventType() == e_cameraEvent)
	{
		CameraEvent* l_cameraEvent = ( CameraEvent* )( p_event );
		if (l_cameraEvent != nullptr)
		{
			std::vector<Entity*>l_cameras = m_collection->getEntityWithComponents( e_cameraComponent );
			if (l_cameras.size() > 0)
			{
				Entity* l_camera = l_cameras[ 0 ];
				if (l_camera != nullptr)
				{
					CameraComponent* a_comp = ( CameraComponent* )( l_camera->getComponent( e_cameraComponent ) );
					if (a_comp != nullptr)
					{
						if (a_comp->m_isActiveCamera)
						{
							newPositionFromEvent( a_comp, l_cameraEvent );
							addRotationFromEvent( a_comp, l_cameraEvent );
							updateCamera( a_comp );
						}
					}
				}
			}
		}
	}
}


void CameraSystem::updateCamera( CameraComponent* p_cameraComp )
{
	glm::vec3 front;
	front.x = cos( glm::radians( p_cameraComp->m_yaw ) ) * cos( glm::radians( p_cameraComp->m_pitch ) );
	front.y = sin( glm::radians( p_cameraComp->m_pitch ) );
	front.z = sin( glm::radians( p_cameraComp->m_yaw ) ) * cos( glm::radians( p_cameraComp->m_pitch ) );
	p_cameraComp->m_front = glm::normalize( front );
	// Also re-calculate the Right and Up vector
	p_cameraComp->m_right = glm::normalize( glm::cross( p_cameraComp->m_front, p_cameraComp->m_worldUp ) );  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	p_cameraComp->m_up = glm::normalize( glm::cross( p_cameraComp->m_right, p_cameraComp->m_front ) );

}


void CameraSystem::addRotationFromEvent( CameraComponent* p_cameraComp, CameraEvent* p_event )
{
	float xOffset = p_event->getRotation().getX();
	float yOffSet = p_event->getRotation().getY();


	p_cameraComp->m_yaw += xOffset;
	p_cameraComp->m_pitch += yOffSet;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped

	if (p_cameraComp->m_pitch > 89.0f)
		p_cameraComp->m_pitch = 89.0f;
	if (p_cameraComp->m_pitch < -89.0f)
		p_cameraComp->m_pitch = -89.0f;
}


void CameraSystem::newPositionFromEvent( CameraComponent* p_cameraComp, CameraEvent* p_event )
{
	float velocity = p_event->velocity;
	if (p_event->direction == CameraEvent::e_forward)
	{
		p_cameraComp->m_pos +=  p_cameraComp->m_front * velocity;
	}
	if (p_event->direction == CameraEvent::e_backward)
	{
		p_cameraComp->m_pos -= p_cameraComp->m_front * velocity;
	}
	if (p_event->direction == CameraEvent::e_left)
	{
		p_cameraComp->m_pos -= p_cameraComp->m_right * velocity;
	}
	if (p_event->direction == CameraEvent::e_right)
	{
		p_cameraComp->m_pos += p_cameraComp->m_right * velocity;
	}
}