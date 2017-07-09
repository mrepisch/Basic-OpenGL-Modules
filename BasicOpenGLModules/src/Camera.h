#pragma once
#include "glew\GL\glew.h"
#include "util\Vector3D.h"

class Camera
{
public:
	Camera(int p_screenWidth, int p_screenHight, float p_depth);
	void setPosition(const VectorF& p_pos);
	const VectorF& getPosition( );
	void move(const VectorF& t_offset);
	virtual ~Camera();
	
	void update();
private:
	int m_screenWidth;
	int m_screenHeight;
	float m_depth;
	VectorF m_position;
};

