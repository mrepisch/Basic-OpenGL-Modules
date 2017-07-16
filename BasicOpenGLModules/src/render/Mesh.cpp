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
	m_vertexBuffer = nullptr;

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
	m_vertecis.clear();
	glDeleteVertexArrays( 1, &m_VAO );
	glDeleteBuffers( 1, &m_vertexBufferID );
	glDeleteBuffers( 1, &m_indicesID );
	delete m_vertexBuffer;
	delete m_texture;
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


GLuint Mesh::getVAO_ID( void )
{
	return m_VAO;
}


void Mesh::generateBuffer( void )
{
	
	m_vertexBuffer = new float[ m_vertecis.size() * 3 ];
	int l_vertexCounter = 0;
	for (int i = 0; i < m_vertecis.size(); ++i)
	{
		m_vertexBuffer[ l_vertexCounter ] = m_vertecis[ i ]->position.getX();
		m_vertexBuffer[ l_vertexCounter + 1] = m_vertecis[ i ]->position.getY();
		m_vertexBuffer[ l_vertexCounter + 2 ] = m_vertecis[ i ]->position.getZ();
		l_vertexCounter += 3;
	}

	m_indices = new int[ m_faces.size() * 3 ];
	int l_indecisCounter = 0;
	for (int i = 0; i < m_faces.size(); ++i)
	{
		m_indices[ l_indecisCounter ] = m_faces[ i ]->vertcies[ 0 ];
		m_indices[ l_indecisCounter + 1 ] = m_faces[ i ]->vertcies[ 1 ];
		m_indices[ l_indecisCounter + 2 ] = m_faces[ i ]->vertcies[ 2 ];
		l_indecisCounter += 3;
	}
	glGenVertexArrays( 1, &m_VAO );
	glGenBuffers( 1, &m_vertexBufferID );
	glGenBuffers( 1, &m_indicesID );
	glBindVertexArray( m_VAO );
	glBindBuffer( GL_ARRAY_BUFFER, m_vertexBufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * m_vertecis.size() * 3, m_vertexBuffer, GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_indicesID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( int ) *m_faces.size() * 3, m_indices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glBindVertexArray( 0 );
}


size_t Mesh::getVertexCount( void )
{
	return m_faces.size() * 3;
}


bool Mesh::hasTexture( void )
{
	return ( m_texture != nullptr );
}


void Mesh::addVertex( Vertex* p_vertex )
{
	if (p_vertex != nullptr)
	{
		m_vertecis.push_back( p_vertex );
	}
}