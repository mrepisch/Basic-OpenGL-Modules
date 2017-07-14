#pragma once
#include "glew\GL\glew.h"
#include "util\Vector3D.h"

class Camera
{
public:
	Camera(int p_screenWidth, int p_screenHight, float p_depth);
	
	virtual ~Camera();

	void setPosition(const util::VectorF& p_pos);
	
	const util::VectorF& getPosition();
	
	void move(const util::VectorF& t_offset);
	
	void rotate( const util::VectorF& t_rotation );

	void update();
private:
	int m_screenWidth;
	int m_screenHeight;
	float m_depth;
	float m_ratio;
	util::VectorF m_position;
	util::VectorF m_rotation;
};