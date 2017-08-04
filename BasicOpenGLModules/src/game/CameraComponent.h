#pragma once

// Internal includes
#include "../component/Component.h"
#include <glm/glm.hpp>

namespace game
{
	class CameraComponent : public component::Component
	{
	public:
		CameraComponent(int p_screenWidth, int p_screenHeight, float p_depth, bool p_isActive = true );

		glm::mat4 getViewMatrix( void );
		
		int m_screenWidth;
		int m_screenHeight;
		float m_depth;
		float m_aspectRatio;

		glm::mat4 m_projection;

		glm::vec3 m_pos;
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;

		float m_yaw;
		float m_pitch;
		void serialize( rapidxml::xml_node<>* p_rootNode );

		bool m_isActiveCamera;

	private:
		glm::mat4 m_view;
	};
}