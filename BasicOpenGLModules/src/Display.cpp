
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
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}



void Display::update()
{

	while (!m_isClosed)
	{
		SDL_GL_SetSwapInterval( 1 );
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		EventDispatcher::Instance().update();
		SystemCollection::Instance().update();

		SDL_GL_SwapWindow( m_window );
		
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


void Display::addSystem( component::System* p_system)
{
	if (p_system != nullptr)
	{
		EventDispatcher::Instance().addSystem( p_system );
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


void Display::closeWindow()
{
	m_isClosed = true;
}