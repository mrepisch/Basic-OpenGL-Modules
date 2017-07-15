#pragma once

// External includes
#include <vector>

// Internal includes
#include "../component/System.h"
#include "../component/Event.h"
#include "KeyInput.h"

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

		void addKeyEvent( KeyInput* p_keyInput );

	private:

		Display* m_display;

		std::vector<KeyInput*>m_keyInputs;
	};
}