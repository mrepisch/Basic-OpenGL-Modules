#pragma once

#include <string>
#include "SDL2\SDL.h"

class Display
{
public:
	Display(int p_with, int p_height, const std::string& p_title);
	virtual ~Display();

	void update();

	bool getIsClosed();

private:
	
	std::string m_windowTitle;
	int m_width;
	int m_height;
	bool m_isClosed;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

