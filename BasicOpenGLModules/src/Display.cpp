

#include "glew\GL\glew.h"
#include <iostream>
#include "Display.h"
#include "util\PLYParser.h"

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
	PLYParser a_parser;
	m_renderer = new GLClassicMeshRender(a_parser.readMeshFromFile("C:\\Users\\episch\\Documents\\plane.ply"));
	m_camera = new Camera(m_width, m_height, 100.0f);
}


Display::~Display()
{
	delete m_renderer;
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


void Display::update()
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_camera->update();

	m_renderer->render();
	SDL_GL_SwapWindow(m_window);
	m_camera->move(VectorF(-0.01f, -0.01f, 0.0f));
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
