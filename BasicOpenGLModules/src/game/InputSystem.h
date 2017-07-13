#pragma once

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"

class Display;

namespace game
{
	class InputSystem : public component::System
	{
	public:
		InputSystem( Display* p_display );
		virtual ~InputSystem();

		void update();

		void receiveEvent( component::Event* p_event );

	private:

		Display* m_display;

	};
}