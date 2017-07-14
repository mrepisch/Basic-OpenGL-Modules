
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