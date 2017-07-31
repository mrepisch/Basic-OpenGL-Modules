
// External includes
#include <SDL2\SDL.h>

// Internal includes
#include "InputSystem.h"
#include "../core/Display.h"
#include "CameraEvent.h"
#include "../util/Vector3D.h"
#include "../component/EventDispatcher.h"


using namespace game;
using namespace component;
using namespace util;

InputSystem::InputSystem( Display* p_display, EntityCollection* p_collection ) : System( e_inputSystem, p_collection )
{
	m_display = p_display;
}


InputSystem::~InputSystem()
{
	m_keyInputs.clear();
}


void InputSystem::update()
{
	SDL_Event l_event;
	while (SDL_PollEvent( &l_event ))
	{
		if (l_event.type == SDL_QUIT)
		{
			m_display->closeWindow();
		}
		for (int i = 0; i < m_keyInputs.size(); ++i)
		{
			if (l_event.type == SDL_KEYDOWN && m_keyInputs[i]->getIsKeyDown())
			{
				if (m_keyInputs[ i ]->hasKeyEvent( l_event.key.keysym.sym ))
				{
					m_keyInputs[ i ]->processEvent( l_event );
				}
			}
			else if (l_event.type == SDL_KEYUP && !m_keyInputs[ i ]->getIsKeyDown())
			{
				if (m_keyInputs[ i ]->hasKeyEvent( l_event.key.keysym.sym ))
				{
					m_keyInputs[ i ]->processEvent( l_event );
				}
			}
		}
		
	}
}


void InputSystem::receiveEvent( Event* p_event )
{

}


void InputSystem::addKeyEvent( KeyInput* p_keyInput )
{
	if (p_keyInput != nullptr)
	{
		m_keyInputs.push_back( p_keyInput );
	}
}