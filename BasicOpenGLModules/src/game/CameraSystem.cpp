
// Internal includes
#include "CameraSystem.h"
#include "..\game\CameraEvent.h"

using namespace component;
using namespace game;

CameraSystem::CameraSystem() : System( e_cameraSystem )
{
	m_camera = new Camera( 800, 600, 150.0f );
}


CameraSystem::~CameraSystem()
{
	delete m_camera;
}


void CameraSystem::update()
{
	m_camera->update();
}


void CameraSystem::receiveEvent( Event* p_event )
{
	if (p_event->getEventType() == e_cameraEvent)
	{
		CameraEvent* l_cameraEvent = ( CameraEvent* )( p_event );
		if (l_cameraEvent != nullptr)
		{
			m_camera->move( l_cameraEvent->getOffset() );
		}
	}
}