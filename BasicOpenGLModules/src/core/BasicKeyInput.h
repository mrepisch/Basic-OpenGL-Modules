#pragma once

#include "game\KeyInput.h"


/**
 * Implementation of the KeyInput interface.
 * It handels the wasd keyinput.
 * @author sascha blank
 */
class BasicKeyInput : public game::KeyInput
{
public:

	/**
	 * Constructor
	 * @author sascha blank
	 */
	BasicKeyInput( void );

	/**
	 * Virtual destructor
	 * @author sascha blank
	 */
	virtual ~BasicKeyInput( void );
	
	/**
	 * Function to process a SDL_Event
	 * @author sascha blank
	 * @param const SDL_Event& referenc on the sdl event
	 */
	void processEvent( const SDL_Event& t_event );
};