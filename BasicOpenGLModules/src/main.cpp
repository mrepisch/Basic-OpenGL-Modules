#include <iostream>
#include <glew\GL\glew.h>
#include "Display.h"
#include "util\Vector3D.h"


int main(int argc, char **argv)
{

	

	Display l_mainWindow(800, 600, "OpenGL Window");

	while (!l_mainWindow.getIsClosed())
	{
		l_mainWindow.update();
	}
	return 0;
}