#pragma once

// External includes
#include <string>
#include <SDL2\SDL.h>


/**
 * Class which represents the Display of the the OpenGL Application.
 * TODO: implement frames per second.
 * @author sascha blank
 */
class Display
{
public:
	/**
	 * Constructor 
	 * @author sascha blank
	 * @param int the with of the screen in pixels
	 * @param int the height of the screen in pixels
	 * @param std::string the window title
	 */
	Display(int p_with, int p_height, const std::string& p_title);

	/**
	 * Virtual destructor
	 * @author sascha blank
	 */
	virtual ~Display();

	/**
	 * Clears the screen. 
	 * This function needs to be called at the start of each frame
	 * @author sascha blank
	 */
	void clearScreen();

	/**
	 * Function to swap the screen.
	 * This function needs to be called at the end of every frame
	 */
	void swap();

	/**
	 * Gets if the windows called the close event
	 * @author sascha blank
	 */
	bool getIsClosed();

	/**
	 * Set frames per second
	 * @author sascha blank
	 */
	void setFPS( int p_fps );

	/**
	 * Function to close the window
	 * @author sascha blank
	 */
	void closeWindow();

private:
	
	// Window title
	std::string m_windowTitle;
	
	// Width of the screen in pixel
	int m_width;

	// Height of the screen in pixel
	int m_height;

	// Is the window closed
	bool m_isClosed;

	// The SDL Winodw pointer
	SDL_Window* m_window;

	// OpenGL context pointer
	SDL_GLContext m_glContext;

	// int for fps calculation
	int m_nextTime;
	
	// frames per second
	int m_fps;
};

