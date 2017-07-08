#include "Mesh.h"
#include <iostream>


Mesh::Mesh()
{
	
}


Mesh::~Mesh()
{
	for (auto a_it = m_faces.begin(); a_it != m_faces.end(); a_it++)
	{
		delete (*a_it);
	}
	m_faces.clear();
}


void Mesh::addFace(Face* p_face)
{
	if (p_face != nullptr)
	{
		m_faces.push_back(p_face);
	}
}



const std::list<Face*>& Mesh::getFaces( void) const
{
	return m_faces;
}

