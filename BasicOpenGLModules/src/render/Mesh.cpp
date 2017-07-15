#include "Mesh.h"
#include <iostream>

using namespace render;

Mesh::Mesh()
{
	m_texture = nullptr;
	m_vertexBuffer = nullptr;
}

Mesh::Mesh(Texture* p_texture)
{
	m_texture = p_texture;
	delete m_vertexBuffer;
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



const std::vector<Face*>& Mesh::getFaces( void) const
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


GLuint Mesh::getVertexBufferID( void )
{
	return m_bufferID;
}


void Mesh::generateBuffer( void )
{
	size_t l_vertexSize = m_faces.size() * 3 * 5 ; 
	m_vertexBuffer = new float[ l_vertexSize ];
	int l_faceCounter = 0;
	for (int i = 0; i < l_vertexSize; i += 15) 
	{
		Vertex* l_vertex = &m_faces[ l_faceCounter ]->vertcies[ 0 ];
		m_vertexBuffer[ i ] = l_vertex->position.getX();
		m_vertexBuffer[ i + 1 ] = l_vertex->position.getY();
		m_vertexBuffer[ i + 2 ] = l_vertex->position.getY();
		m_vertexBuffer[ i + 3 ] = l_vertex->textureCords.getX();
		m_vertexBuffer[ i + 4 ] = l_vertex->textureCords.getY();

		l_vertex = &m_faces[ l_faceCounter ]->vertcies[ 1 ];
		m_vertexBuffer[ i + 5 ] = l_vertex->position.getX();
		m_vertexBuffer[ i + 6 ] = l_vertex->position.getY();
		m_vertexBuffer[ i + 7 ] = l_vertex->position.getY();
		m_vertexBuffer[ i + 8 ] = l_vertex->textureCords.getX();
		m_vertexBuffer[ i + 9 ] = l_vertex->textureCords.getY();

		l_vertex = &m_faces[ l_faceCounter ]->vertcies[ 2 ];
		m_vertexBuffer[ i + 10 ] = l_vertex->position.getX();
		m_vertexBuffer[ i + 11 ] = l_vertex->position.getY();
		m_vertexBuffer[ i + 12 ] = l_vertex->position.getY();
		m_vertexBuffer[ i + 13 ] = l_vertex->textureCords.getX();
		m_vertexBuffer[ i + 14 ] = l_vertex->textureCords.getY();

		++l_faceCounter;
	}

	for (int i = 0; i < l_vertexSize; ++i)
	{
		std::cout << m_vertexBuffer[ i ] << std::endl;
	}
	glGenBuffers( 1, &m_bufferID );
	glBindBuffer( GL_ARRAY_BUFFER, m_bufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * l_vertexSize , m_vertexBuffer, GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


size_t Mesh::getVertexCount( void )
{
	return m_faces.size() * 3;
}


bool Mesh::hasTexture( void )
{
	return ( m_texture != nullptr );
}
