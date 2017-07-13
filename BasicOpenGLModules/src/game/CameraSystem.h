#pragma once

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"
#include "../Camera.h"

namespace game
{
	class CameraSystem : public component::System
	{
	public:
		CameraSystem();
		virtual ~CameraSystem();

		void update();

		void receiveEvent( component::Event* p_event );

	private:

		Camera* m_camera;
	};
}