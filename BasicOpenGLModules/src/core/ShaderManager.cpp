#include <iostream>

#include "ShaderManager.h"
#include "../util/Util.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "../util/Util.h"
using namespace core;
using namespace util;

const std::string S_BASEPATHSHADERS = Util::getBasePath() + "/src/shader/";

ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{

}


void ShaderManager::addShader( const std::string& t_shaderName, EnShaderType t_type, const std::string& t_shaderFile, const std::string& t_programName )
{
	std::string l_shaderStr = util::Util::readFile( (S_BASEPATHSHADERS + t_shaderFile).c_str());
	GLuint l_shaderID;
	if( t_type == e_vertex )
	{ 
		l_shaderID = glCreateShader( GL_VERTEX_SHADER );
	}
	else if (t_type == e_fragment)
	{
		l_shaderID = glCreateShader( GL_FRAGMENT_SHADER );
	}
	
	const char* l_shaderSource = l_shaderStr.c_str();
	glShaderSource( l_shaderID, 1, &l_shaderSource, NULL );
	glCompileShader( l_shaderID );
	int  success;
	char infoLog[ 512 ];
	glGetShaderiv( l_shaderID, GL_COMPILE_STATUS, &success );
	if (!success)
	{
		glGetShaderInfoLog( l_shaderID, 512, NULL, infoLog );
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glAttachShader( m_shaderPrograms[t_programName], l_shaderID );
	glDeleteShader( l_shaderID );
	
}

void ShaderManager::createShaderProgram( const std::string& t_programName )
{
	GLuint l_shaderProgramID = glCreateProgram();
	m_shaderPrograms.insert( std::make_pair( t_programName, l_shaderProgramID ) );
}


void ShaderManager::compile( void )
{
	char l_infoLog[ 512 ];
	for (auto const &iter : m_shaderPrograms)
	{
		int l_succes;
		glLinkProgram( iter.second );

		glGetProgramiv( iter.second, GL_LINK_STATUS, &l_succes );
		if (!l_succes)
		{
			glGetProgramInfoLog( iter.second, 512, NULL, l_infoLog );
			std::cout << "ERROR LINKING SHADER PROGRAM FAILD\n" << l_infoLog << std::endl;
		}
	}
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), ( void* )0 );
	glEnableVertexAttribArray( 0 );
}


GLuint ShaderManager::getShaderProgramID( const std::string& p_name )
{
	return m_shaderPrograms[ p_name ];
}


void ShaderManager::setVector( glm::vec3 p_vec, const std::string& p_uniformName, const std::string& p_shaderProgramName )
{
	setVector( p_vec, p_uniformName, getShaderProgramID( p_shaderProgramName ) );
}

void ShaderManager::setVector( glm::vec3 p_vec, const std::string& p_uniformName, GLuint p_shaderProgrammID )
{
	unsigned int l_vectorLoc = glGetUniformLocation( p_shaderProgrammID, p_uniformName.c_str() );
	glUniform3fv( l_vectorLoc, 1, glm::value_ptr( p_vec ) );
}

void ShaderManager::setMatrix( glm::mat4 p_matrix, const std::string& p_uniformName, const std::string& p_shaderProgramName )
{
	setMatrix( p_matrix, p_uniformName, getShaderProgramID( p_shaderProgramName ) );
}

void ShaderManager::setMatrix( glm::mat4 p_matrix, const std::string& p_uniformName, GLuint p_shaderProgrammID )
{
	unsigned int l_matrixLoc = glGetUniformLocation( p_shaderProgrammID, p_uniformName.c_str() );
	glUniformMatrix4fv( l_matrixLoc, 1, GL_FALSE, glm::value_ptr( p_matrix ) );
}


void ShaderManager::useProgram( const std::string& p_name )
{
	useProgram( getShaderProgramID( p_name ) );
}


void ShaderManager::useProgram( GLuint p_name )
{
	glUseProgram( p_name );
}


void ShaderManager::setFloat( float p_value, const std::string& p_uniformName, GLuint p_shaderProgrammID )
{
	unsigned int l_uniformID = glGetUniformLocation( p_shaderProgrammID, p_uniformName.c_str() );
	glUniform1f( l_uniformID, p_value );
}


void ShaderManager::setFloat( float p_value, const std::string& p_uniformName, const std::string& p_shaderProgrammName )
{
	setFloat( p_value, p_uniformName, getShaderProgramID( p_shaderProgrammName ) );
}


void ShaderManager::setInt( int p_value, const std::string& p_uniformName, GLuint p_shaderProgramID )
{
	unsigned int l_unifromLoc = glGetUniformLocation( p_shaderProgramID, p_uniformName.c_str() );
	glUniform1i( l_unifromLoc, p_value );
}


void ShaderManager::setInt( int p_value, const std::string& p_uniformName, const std::string& p_shaderProgramName )
{
	setInt( p_value, p_uniformName, getShaderProgramID( p_shaderProgramName ) );
}