#pragma once
#include<glew\GL\glew.h>
#include "IMeshRender.h"
#include "Mesh.h"
class GLClassicMeshRender : public IMeshRender
{
public:
	GLClassicMeshRender( Mesh* p_mesh );

	void init();
	void render();

private:
	GLfloat* m_vertexBuffer;
	GLuint m_vertexArrayID;
	Mesh* m_mesh;
};