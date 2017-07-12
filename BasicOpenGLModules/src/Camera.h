#pragma once
#include "glew\GL\glew.h"
#include "util\Vector3D.h"

class Camera
{
public:
	Camera(int p_screenWidth, int p_screenHight, float p_depth);
	
	void setPosition(const util::VectorF& p_pos);
	
	const util::VectorF& getPosition();
	
	void move(const util::VectorF& t_offset);
	
	virtual ~Camera();

	void update();
private:
	int m_screenWidth;
	int m_screenHeight;
	float m_depth;
	util::VectorF m_position;
	util::VectorF m_rotation;
};