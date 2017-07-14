#pragma once

// External includes
#include <SDL2\SDL.h>
#include <vector>

namespace game
{
	/**
	 * Base class for processing SDL Key Events.
	 * In order to use this class you have to implement the processEvent function.
	 * Just add SDL keys ( f.e SDLK_a ) with the addKey function and use it in the processEvent Function
	 * With the setIsKeyDown function you can define if the key events shoud be processed as KEYDOWN or KEYUP Event.
	 * The default is KEYDOWN.
	 * @author sascha blank
	 */
	class KeyInput
	{
	public:

		/**
		 * Constructor
		 * @author sascha blank
		 */
		KeyInput();

		/**
		 * Virtual destructor
		 * @author sascha blank
		 */
		virtual ~KeyInput();

		/**
		 * Function to add a SDL key to handle 
		 * @author sascha blank
		 */
		void addKey( int p_SDL_KEY );

		/**
		 * Define if the input shoud be processed as KEYUP or KEYDOWN event
		 * @author sascha blank
		 */
		void setIsKeyDown( bool p_useKeyDown );

		/**
		 * Return m_useKeyDown
		 * @author sascha blank
		 */
		bool getIsKeyDown( void );

		/**
		 * Abstract Function since this is just a base class.
		 * Implement this function to process the keyevents.
		 * @author sascha blank
		 */
		virtual void processInput( void ) = 0;

	protected:
		// vector with the keys
		std::vector<int>m_SDL_Keys;

		// Defines if the the Keyevents shoud be processed as KEYUP or KEYDOW events.
		// Default is KEYDOWN
		bool m_useKeyDown;
	};
}