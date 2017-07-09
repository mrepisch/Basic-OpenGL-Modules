#pragma once

#include <string>
#include "SDL2\SDL.h"
#include "render\GLClassicMeshRender.h"
#include "Camera.h"

class Display
{
public:
	Display(int p_with, int p_height, const std::string& p_title);
	virtual ~Display();
	void update();

	bool getIsClosed();

private:
	
	std::string m_windowTitle;
	
	GLClassicMeshRender* m_renderer;
	int m_width;
	int m_height;
	bool m_isClosed;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	Camera* m_camera;
};

