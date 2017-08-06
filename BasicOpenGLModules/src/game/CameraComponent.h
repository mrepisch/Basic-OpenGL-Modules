#pragma once

// External includes
#include <glm/glm.hpp>

// Internal includes
#include "../component/Component.h"


namespace game
{
	/**
	 * CameraComponent for an Entity. If this component is uses with an Entity it will be placed as 
	 * egoperspective Camera with the current CameraSystem
	 * @author sascha blank
	 */
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
		bool m_isActiveCamera;

		/**
		 * Abstract function to serialize the component.
		 * It uses a xml format.
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the node to append the component node
		 */
		void serialize( rapidxml::xml_node<>* p_rootNode );

		/**
		 * Function to read the component data from a xml node
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the component node
		 */
		void deserialize( rapidxml::xml_node<>* p_node );



	private:
		glm::mat4 m_view;
	};
}