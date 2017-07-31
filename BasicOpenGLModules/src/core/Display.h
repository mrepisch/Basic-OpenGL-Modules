#pragma once

// External includes

#include <string>
#include <SDL2\SDL.h>

// Internal includes

class Display
{
public:
	Display(int p_with, int p_height, const std::string& p_title);

	virtual ~Display();

	void clearScreen();

	void swap();

	bool getIsClosed();

	void setFPS( int p_fps );

	void closeWindow();

private:
	

	std::string m_windowTitle;
	
	int m_width;

	int m_height;

	bool m_isClosed;

	SDL_Window* m_window;

	SDL_GLContext m_glContext;

	int m_nextTime;
	

	int m_fps;
};

