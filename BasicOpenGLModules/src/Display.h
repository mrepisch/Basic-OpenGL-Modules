#pragma once

// External includes
#include <string>
#include <SDL2\SDL.h>

// Internal includes
#include "Camera.h"
#include "component\System.h"
#include "component\Event.h"
#include "component\Entity.h"

class Display
{
public:
	Display(int p_with, int p_height, const std::string& p_title);

	virtual ~Display();

	void update();

	bool getIsClosed();

	void setFPS( int p_fps );

	void addSystem( component::System* p_system, component::EnEventType p_eventType );

	void addEntity( component::Entity* p_entity );

private:
	
	Uint32 getTimeLeft( void );

	std::string m_windowTitle;
	
	int m_width;

	int m_height;

	bool m_isClosed;

	SDL_Window* m_window;

	SDL_GLContext m_glContext;

	Camera* m_camera;

	Uint32 m_nextTime;

	int m_fps;
};

