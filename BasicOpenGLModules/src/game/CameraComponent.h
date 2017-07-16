#pragma once

// Internal includes
#include "../component/Component.h"
#include <glm/glm.hpp>

namespace game
{
	class CameraComponent : public component::Component
	{
	public:
		CameraComponent(int p_screenWidth, int p_screenHeight, float p_depth);

		glm::mat4 getViewMatrix( void );
		int m_screenWidth;
		int m_screenHeight;
		float m_depth;
		float m_aspectRatio;

		
		glm::mat4 m_projection;

		glm::vec3 m_pos;
		glm::vec3 m_rot;
		glm::vec3 m_scl;

		glm::vec3 m_cameraFront;
		glm::vec3 m_cameraUp;

		glm::vec3 m_right;

	private:
		glm::mat4 m_view;
	};
}