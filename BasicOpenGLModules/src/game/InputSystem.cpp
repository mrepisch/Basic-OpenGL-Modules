
// External includes
#include <SDL2\SDL.h>

// Internal includes
#include "InputSystem.h"
#include "../Display.h"
#include "CameraEvent.h"
#include "../util/Vector3D.h"
#include "../component/EventDispatcher.h"


using namespace game;
using namespace component;
using namespace util;

InputSystem::InputSystem( Display* p_display ) : System( e_inputSystem )
{
	m_display = p_display;
}


InputSystem::~InputSystem()
{

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
		else if (l_event.type == SDL_KEYDOWN)
		{
			switch (l_event.key.keysym.sym)
			{
				case SDLK_w:
				{
					CameraEvent* l_cameraEvent = new CameraEvent();
					l_cameraEvent->setOffset( VectorF( 0.0f, 0.0f, -0.1f ) );
					EventDispatcher::Instance().addEvent( l_cameraEvent );
					break;
				}
				case SDLK_a:
				{
					CameraEvent* l_cameraEvent = new CameraEvent();
					l_cameraEvent->setOffset( VectorF( -0.1f, 0.0f, 0.0f ) );
					EventDispatcher::Instance().addEvent( l_cameraEvent );
					break;
				}
				case SDLK_s:
				{
					CameraEvent* l_cameraEvent = new CameraEvent();
					l_cameraEvent->setOffset( VectorF( 0.0f, 0.0f, 0.1f ) );
					EventDispatcher::Instance().addEvent( l_cameraEvent );
					break;
				}
				case SDLK_d:
				{
					CameraEvent* l_cameraEvent = new CameraEvent();
					l_cameraEvent->setOffset( VectorF( 0.1f, 0.0f, 0.0f ) );
					EventDispatcher::Instance().addEvent( l_cameraEvent );
					break;
				}
				default:
					break;
			}
		}
	}
}


void InputSystem::receiveEvent( Event* p_event )
{

}