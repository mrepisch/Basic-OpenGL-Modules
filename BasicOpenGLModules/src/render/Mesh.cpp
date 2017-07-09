#include "Mesh.h"
#include <iostream>

using namespace render;

Mesh::Mesh()
{
	m_texture = nullptr;
}

Mesh::Mesh(Texture* p_texture)
{
	m_texture = p_texture;
}

Mesh::Mesh(const char* p_textureFilePath)
{
	m_texture = new Texture(p_textureFilePath);
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


GLuint Mesh::getTextureID()
{
	return m_texture->getTextureID();
}

void Mesh::setTexture(Texture* p_texture)
{
	m_texture = p_texture;
}

