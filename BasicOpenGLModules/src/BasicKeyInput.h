#pragma once

#include "game\KeyInput.h"


class BasicKeyInput : public game::KeyInput
{
public:
	BasicKeyInput( void );
	virtual ~BasicKeyInput( void );


	void processEvent( const SDL_Event& t_event );
};