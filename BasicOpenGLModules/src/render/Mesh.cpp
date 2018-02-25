// External includes
#include <iostream>

// Internal includes
#include "Mesh.h"

using namespace render;

Mesh::Mesh()
{
	m_material = nullptr;
	
	m_vertexBuffer = nullptr;
	m_shaderProgramName = std::string();
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
	
	delete m_material;
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


GLuint Mesh::getVAO_ID( void )
{
	return m_VAO;
}


void Mesh::generateBuffer( void )
{
	m_vertexBuffer = new float[ m_vertecis.size() * 11 ];
	int l_vertexCounter = 0;
	for (int i = 0; i < m_vertecis.size(); ++i)
	{
		m_vertexBuffer[ l_vertexCounter ] = m_vertecis[ i ]->position.getX();
		m_vertexBuffer[ l_vertexCounter + 1] = m_vertecis[ i ]->position.getY();
		m_vertexBuffer[ l_vertexCounter + 2 ] = m_vertecis[ i ]->position.getZ();

		m_vertexBuffer[ l_vertexCounter + 3 ] = m_vertecis[ i ]->textureCords.getX();
		m_vertexBuffer[ l_vertexCounter + 4 ] = m_vertecis[ i ]->textureCords.getY();

		m_vertexBuffer[ l_vertexCounter + 5 ] = m_vertecis[ i ]->color.getX();
		m_vertexBuffer[ l_vertexCounter + 6 ] = m_vertecis[ i ]->color.getY();
		m_vertexBuffer[ l_vertexCounter + 7 ] = m_vertecis[ i ]->color.getZ();

		m_vertexBuffer[ l_vertexCounter + 8 ] = m_vertecis[ i ]->normal.getX();
		m_vertexBuffer[ l_vertexCounter + 9 ] = m_vertecis[ i ]->normal.getY();
		m_vertexBuffer[ l_vertexCounter + 10 ] = m_vertecis[ i ]->normal.getZ();
		l_vertexCounter += 11;
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
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * m_vertecis.size() * 11, m_vertexBuffer, GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_indicesID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( int ) * m_faces.size() * 3, m_indices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), ( void* )0 );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), ( void* )( 3 * sizeof( float ) ) );
	glEnableVertexAttribArray( 1 );

	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), ( void* )( 5 * sizeof( float ) ) );
	glEnableVertexAttribArray( 2 );

	glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), ( void* )( 8 * sizeof( float ) ) );
	glEnableVertexAttribArray( 3 );
}


size_t Mesh::getVertexCount( void )
{
	return m_faces.size() * 3;
}


void Mesh::addVertex( Vertex* p_vertex )
{
	if (p_vertex != nullptr)
	{
		m_vertecis.push_back( p_vertex );
	}
}


void Mesh::setShaderProgramName( const std::string& p_shaderProgramm )
{
	m_shaderProgramName = p_shaderProgramm;
}


const std::string& Mesh::getShaderProgramNameName( void )
{
	return m_shaderProgramName;
}


void Mesh::setMaterial( Material* p_material )
{
	if (p_material != nullptr)
	{
		m_material = p_material;
	}
}


Material* Mesh::getMaterial( void )
{
	return m_material;
}


GLuint Mesh::generateInstaciatetBuffer( int p_amount, glm::mat4* modelMatrices )
{
	generateBuffer();
	GLuint r_bufferID;
	glGenBuffers( 1, &r_bufferID );
	glBindBuffer( GL_ARRAY_BUFFER, r_bufferID );
	glBufferData( GL_ARRAY_BUFFER, p_amount * sizeof( glm::mat4 ), &modelMatrices[ 0 ], GL_STATIC_DRAW );
	
	for (unsigned int i = 0; i < m_vertecis.size(); i++)
	{
		unsigned int VAO = m_VAO;
		glBindVertexArray( VAO );
		// set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray( 3 );
		glVertexAttribPointer( 3, 4, GL_FLOAT, GL_FALSE, sizeof( glm::mat4 ), ( void* )0 );
		glEnableVertexAttribArray( 4 );
		glVertexAttribPointer( 4, 4, GL_FLOAT, GL_FALSE, sizeof( glm::mat4 ), ( void* )( sizeof( glm::vec4 ) ) );
		glEnableVertexAttribArray( 5 );
		glVertexAttribPointer( 5, 4, GL_FLOAT, GL_FALSE, sizeof( glm::mat4 ), ( void* )( 2 * sizeof( glm::vec4 ) ) );
		glEnableVertexAttribArray( 6 );
		glVertexAttribPointer( 6, 4, GL_FLOAT, GL_FALSE, sizeof( glm::mat4 ), ( void* )( 3 * sizeof( glm::vec4 ) ) );

		glVertexAttribDivisor( 3, 1 );
		glVertexAttribDivisor( 4, 1 );
		glVertexAttribDivisor( 5, 1 );
		glVertexAttribDivisor( 6, 1 );

		glBindVertexArray( 0 );
	}
	return 0;
}