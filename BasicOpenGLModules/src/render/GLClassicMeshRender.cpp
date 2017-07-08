#include "GLClassicMeshRender.h"

GLClassicMeshRender::GLClassicMeshRender(Mesh* p_mesh)
{
	if (p_mesh != nullptr)
	{
		m_mesh = p_mesh;
	}
	else
	{
		m_mesh = nullptr;
	}
}


void GLClassicMeshRender::init(void)
{

}


void GLClassicMeshRender::render(void)
{
	if (m_mesh != nullptr)
	{
		glBegin(GL_TRIANGLES);
		auto l_meshes = m_mesh->getFaces();
		for (auto l_iter = l_meshes.cbegin(); l_iter != l_meshes.cend(); ++l_iter)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f((*l_iter)->vertcies[0].position.getX(), (*l_iter)->vertcies[0].position.getY(), (*l_iter)->vertcies[0].position.getZ());
			glVertex3f((*l_iter)->vertcies[1].position.getX(), (*l_iter)->vertcies[1].position.getY(), (*l_iter)->vertcies[1].position.getZ());
			glVertex3f((*l_iter)->vertcies[2].position.getX(), (*l_iter)->vertcies[2].position.getY(), (*l_iter)->vertcies[2].position.getZ());
		}
		glEnd();
	}
}