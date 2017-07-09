#include "Camera.h"



Camera::Camera(int p_screenWidth, int p_screenHight, float p_depth)
{
	m_position.set(0.0f, 0.0f, 0.0f);
}


Camera::~Camera()
{
	// empty body
}


void Camera::update()
{

	glFrustum(-1.0, 1.0f, -1.0, 1.0, 0.1, 1000.0);
	glLoadIdentity();
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
	m_position = m_position + VectorF( t_offset.getX()*-1, t_offset.getY() * -1, t_offset.getZ() * -1);
}