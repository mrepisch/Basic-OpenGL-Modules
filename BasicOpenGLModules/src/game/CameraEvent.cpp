#include "CameraEvent.h"


using namespace game;
using namespace component;
using namespace util;

CameraEvent::CameraEvent() : Event( e_cameraEvent)
{
	m_offset.set( 0.0f, 0.0f, 0.0f );
	m_rotation.set( 0.0f, 0.0f, 0.0f );
}

CameraEvent::~CameraEvent()
{
	
}


const VectorF& CameraEvent::getOffset() const
{
	return m_offset;
}


const VectorF& CameraEvent::getRotation() const
{
	return m_rotation;
}


void CameraEvent::setOffset( const VectorF& p_offset )
{
	m_offset = p_offset;
}


void CameraEvent::setRotation( const VectorF& p_rotation )
{
	m_rotation = p_rotation;
}