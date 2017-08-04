#include "CameraEvent.h"


using namespace game;
using namespace component;
using namespace util;

CameraEvent::CameraEvent() : Event( e_cameraEvent)
{

	m_rotation.set( 0.0f, 0.0f, 0.0f );
	velocity = 1.0f;
	direction = e_none;
}

CameraEvent::~CameraEvent()
{

}

const VectorF& CameraEvent::getRotation() const
{
	return m_rotation;
}


void CameraEvent::setRotation( const VectorF& p_rotation )
{
	m_rotation = p_rotation;
}