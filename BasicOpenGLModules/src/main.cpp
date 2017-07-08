#include <iostream>
#include <glew\GL\glew.h>
#include "Display.h"
#include "util\Vector3D.h"
int main(int argc, char **argv)
{
	Display l_mainWindow(800, 600, "OpenGL Window");
	Vector3D<float>a_test(10, 20, 30);
	
	while (!l_mainWindow.getIsClosed())
	{
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		l_mainWindow.update();
	}
	return 0;
}