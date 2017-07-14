#include "Camera.h"

using namespace util;

Camera::Camera(int p_screenWidth, int p_screenHight, float p_depth)
{
	m_position.set(0.0f, 0.0f, -2.0f);
	m_rotation.set(0.0f, 0.0f, 0.0f);	
	m_ratio = (float)(p_screenWidth / p_screenHight);
	m_depth = p_depth;
}


Camera::~Camera()
{
	// empty body
}


void Camera::update()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glFrustum( 0.5, -0.5, -0.5, 0.5, 1, m_depth );
	glRotated(m_rotation.getX(), 1.0, 0.0, 0.0);
	glRotated(m_rotation.getY(), 0.0, 1.0, 0.0);
	glRotated(m_rotation.getZ(), 0.0, 0.0, 1.0);
	glTranslatef(m_position.getX(), m_position.getY(), m_position.getZ());
}


void Camera::setPosition(const VectorF& p_pos)
{
	m_position = p_pos;
}


const VectorF& Camera::getPosition()
{
	return m_position;
}


void Camera::move(const VectorF& t_offset)
{
	m_position = m_position + VectorF(t_offset.getX(), t_offset.getY(), t_offset.getZ());
}


void Camera::rotate( const util::VectorF& t_rotation )
{
	m_rotation = m_rotation + VectorF( t_rotation.getX(), t_rotation.getY(), t_rotation.getZ() );
}