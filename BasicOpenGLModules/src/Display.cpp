

#include "glew\GL\glew.h"
#include <iostream>
#include "Display.h"

Display::Display(int p_with, int p_height, const std::string& p_title)
{
	m_height = p_height;
	m_width = p_with;
	m_windowTitle = p_title;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);
	GLenum l_status = glewInit();
	if (l_status != GLEW_OK)
	{
		std::cout << "PROBLEM WITH GLEW INIT" << std::endl;
	}
	m_isClosed = false;
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


void Display::update()
{
	SDL_GL_SwapWindow(m_window);
	SDL_Event l_event;
	while (SDL_PollEvent(&l_event))
	{
		if( l_event.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
	}
}


bool Display::getIsClosed()
{
	return m_isClosed;
}
