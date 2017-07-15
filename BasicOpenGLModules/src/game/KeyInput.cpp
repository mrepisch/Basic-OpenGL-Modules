
// Internal includes
#include "KeyInput.h"

using namespace game;

KeyInput::KeyInput( )
{
	m_useKeyDown = true;
}


KeyInput::~KeyInput()
{

}


void KeyInput::addKey( int p_SDL_KEY )
{
	m_SDL_Keys.push_back( p_SDL_KEY );
}


void KeyInput::setIsKeyDown( bool p_useKeyDown )
{
	m_useKeyDown = p_useKeyDown;
}


bool KeyInput::getIsKeyDown( void )
{
	return m_useKeyDown;
}


bool KeyInput::hasKeyEvent( int p_SDL_Key )
{
	bool r_hasKeyEvent = false;
	for (int i = 0; i < m_SDL_Keys.size(); ++i)
	{
		if (m_SDL_Keys[ i ] == p_SDL_Key)
		{
			r_hasKeyEvent = true;
			break;
		}
	}
	return r_hasKeyEvent;
}