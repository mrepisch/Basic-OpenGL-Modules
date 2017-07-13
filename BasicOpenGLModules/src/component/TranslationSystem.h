#pragma once

// Internal includes
#include "System.h"
#include "System.h"

namespace component
{
	class TranslationSystem : public System
	{
	public:

		TranslationSystem();

		void update();

		void receiveEvent( Event* p_event );
	private:

	};
}