
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

CameraSystem::CameraSystem( GLuint p_shaderID ) : System( e_cameraSystem )
{
	m_shaderID = p_shaderID;
}


CameraSystem::~CameraSystem()
{

}


void CameraSystem::update()
{
	std::vector<Entity*>l_cameras = EntityCollection::Instance().getEntityWithComponents( e_cameraComponent );
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
	}
}


void CameraSystem::receiveEvent( Event* p_event )
{
	if (p_event->getEventType() == e_cameraEvent)
	{
		CameraEvent* l_cameraEvent = ( CameraEvent* )( p_event );
		if (l_cameraEvent != nullptr)
		{
			std::vector<Entity*>l_cameras = EntityCollection::Instance().getEntityWithComponents( e_cameraComponent );
			if (l_cameras.size() > 0)
			{
				Entity* l_camera = l_cameras[ 0 ];
				if (l_camera != nullptr)
				{
					CameraComponent* a_comp = ( CameraComponent* )( l_camera->getComponent( e_cameraComponent ) );
					if (a_comp != nullptr)
					{
						a_comp->m_pos += glm::vec3( l_cameraEvent->getOffset().getX(), l_cameraEvent->getOffset().getY(), l_cameraEvent->getOffset().getZ() );
						updateCamera( a_comp );
					}

				}
			}
		}
	}
}



void CameraSystem::updateCamera( CameraComponent* p_cameraComp )
{
	/*glm::vec3 front;
	front.x = cos( glm::radians( Yaw ) ) * cos( glm::radians( Pitch ) );
	front.y = sin( glm::radians( Pitch ) );
	front.z = sin( glm::radians( Yaw ) ) * cos( glm::radians( Pitch ) );
	Front = glm::normalize( front );
	// Also re-calculate the Right and Up vector
	Right = glm::normalize( glm::cross( Front, WorldUp ) );  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize( glm::cross( Right, Front ) );*/

	glm::vec3 l_front;
	l_front.x = cos( glm::radians( YAW ) ) * cos( glm::radians( PITCH ) );
	l_front.y = sin( glm::radians( PITCH ) );
	l_front.z = sin( glm::radians( YAW ) ) * cos( glm::radians( PITCH ) );
	p_cameraComp->m_cameraFront = glm::normalize( l_front );
	p_cameraComp->m_right = glm::normalize( glm::cross( p_cameraComp->m_cameraFront, p_cameraComp->m_cameraUp ) );  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
}