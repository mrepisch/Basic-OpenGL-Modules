
// External includes
#include <iostream>
#include <glew\GL\glew.h>

// Internal includes
#include "Display.h"
#include "component\EventDispatcher.h"
#include "component\SystemCollection.h"
#include "component\EntityCollection.h"

using namespace util;
using namespace component;

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

	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);                         // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLenum l_status = glewInit();
	if (l_status != GLEW_OK)
	{
		std::cout << "PROBLEM WITH GLEW INIT" << std::endl;
	}
	m_isClosed = false;
	
	m_camera = new Camera(m_width, m_height, 100.0f);
	
	
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


Uint32 Display::getTimeLeft()
{
	Uint32 l_now;
	l_now = SDL_GetTicks();
	if (m_nextTime <= l_now)
	{
		return 0;
	}
	return m_nextTime - l_now;
}


void Display::update()
{
	m_nextTime = SDL_GetTicks() + m_fps;
	while (!m_isClosed)
	{
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		m_camera->update();
		SystemCollection::Instance().update();

		SDL_GL_SwapWindow( m_window );
		SDL_Event l_event;
		SDL_PollEvent( &l_event );
		if (l_event.type == SDL_QUIT)
		{
			m_isClosed = true;
		}		
		SDL_Delay( getTimeLeft() );
		m_nextTime += m_fps;
	}
}


void Display::setFPS( int p_fps )
{
	m_fps = p_fps;
}


bool Display::getIsClosed()
{
	return m_isClosed;
}


void Display::addSystem( component::System* p_system, component::EnEventType p_eventType )
{
	if (p_system != nullptr)
	{
		EventDispatcher::Instance().addSystem( p_eventType, p_system );
		SystemCollection::Instance().addSystem( p_system );
	}
}

void Display::addEntity( Entity* p_entity )
{
	if (p_entity != nullptr)
	{
		EntityCollection::Instance().addEntity( p_entity );
	}
}