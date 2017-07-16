
// External includes
#include <vector>
#include<glew\GL\glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Internal includes
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "../component/Entity.h"
#include "../component/TranslationComponent.h"
#include "../component/EntityCollection.h"
#include "../util/Util.h"
#include "../game/CameraComponent.h"
using namespace render;
using namespace component;
using namespace game;

RenderSystem::RenderSystem() : System( e_renderSystem)
{
	m_vertexShader = util::Util::readShaderFile( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\src\\shader\\basic_vertex.txt" );
	m_fragmentShader = util::Util::readShaderFile( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\src\\shader\\fragment_shader.txt" );

	m_vertexShaderID = glCreateShader( GL_VERTEX_SHADER );
	const char* l_shaderSource = m_vertexShader.c_str();
	glShaderSource( m_vertexShaderID, 1, &l_shaderSource , NULL );
	glCompileShader( m_vertexShaderID );
	int  success;
	char infoLog[ 512 ];
	glGetShaderiv( m_vertexShaderID, GL_COMPILE_STATUS, &success );
	if (!success)
	{
		glGetShaderInfoLog( m_vertexShaderID, 512, NULL, infoLog );
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_fragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );
	const char* a_fragmentShaderSource = m_fragmentShader.c_str();
	glShaderSource( m_fragmentShaderID, 1, &a_fragmentShaderSource, NULL );
	glCompileShader( m_fragmentShaderID );

	glGetShaderiv( m_fragmentShaderID, GL_COMPILE_STATUS, &success );
	if (!success)
	{
		glGetShaderInfoLog( m_fragmentShaderID, 512, NULL, infoLog );
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	m_shaderProgramID = glCreateProgram();
	glAttachShader( m_shaderProgramID, m_vertexShaderID );
	glAttachShader( m_shaderProgramID, m_fragmentShaderID );
	glLinkProgram( m_shaderProgramID );
	
	glGetProgramiv( m_shaderProgramID, GL_LINK_STATUS, &success );
	if (!success)
	{
		glGetProgramInfoLog( m_shaderProgramID, 512, NULL, infoLog );
		std::cout << "ERROR LINKING SHADER PROGRAM FAILD\n" << infoLog << std::endl;
	}

	//glUseProgram( m_shaderProgramID );
	glDeleteShader( m_vertexShaderID );
	glDeleteShader( m_fragmentShaderID );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), ( void* )0 );
	glEnableVertexAttribArray( 0 );

	m_camera =  EntityCollection::Instance().getEntityWithComponents( e_cameraComponent )[ 0 ];

}

RenderSystem::~RenderSystem()
{

}



GLuint RenderSystem::getShaderProgramID()
{
	return m_shaderProgramID;
}

void RenderSystem::update()
{

	// handle camera
	CameraComponent* l_cameraComp = (CameraComponent*)(m_camera->getComponent( e_cameraComponent ) );
	if (l_cameraComp != nullptr)
	{
		glm::mat4 l_view;
		glm::mat4 l_projection;
		l_projection = glm::perspective( glm::radians( 45.0f ), ( float )l_cameraComp->m_screenWidth / ( float )l_cameraComp->m_screenHeight, 0.1f, l_cameraComp->m_depth );
		//l_view = glm::translate( l_view, l_cameraComp->m_pos);

		unsigned int l_projectionLoc = glGetUniformLocation( m_shaderProgramID, "projection" );
		glUniformMatrix4fv( l_projectionLoc, 1, GL_FALSE, glm::value_ptr( l_projection ) );

		unsigned int l_viewLoc = glGetUniformLocation( m_shaderProgramID, "view" );
		glUniformMatrix4fv( l_viewLoc, 1, GL_FALSE, glm::value_ptr( l_cameraComp->getViewMatrix() ) );
	}
	

	std::vector<Entity*>l_entitys = EntityCollection::Instance().getEntityWithComponents( e_renderComponent );
	for (int i = 0; i < l_entitys.size(); ++i)
	{
		RenderComponent* l_renderComponent = ( RenderComponent*) l_entitys[ i ]->getComponent( e_renderComponent );
		TranslationComponent* l_translationComponent = ( TranslationComponent* )l_entitys[ i ]->getComponent( e_translationComponent );
		if (l_renderComponent != nullptr && l_translationComponent != nullptr)
		{
			glm::mat4 l_trans;
			l_trans = glm::translate( l_trans, glm::vec3( l_translationComponent->m_position.getX(),
				l_translationComponent->m_position.getY(),
				l_translationComponent->m_position.getZ()) );

			l_trans = glm::rotate( l_trans, l_translationComponent->m_rotation.getX(), glm::vec3( 1.0, 0.0, 0.0 ) );
			l_trans = glm::rotate( l_trans, l_translationComponent->m_rotation.getY(), glm::vec3( 0.0, 1.0, 0.0 ) );
			l_trans = glm::rotate( l_trans, l_translationComponent->m_rotation.getZ(), glm::vec3( 0.0, 0.0, 1.0 ) );

			l_trans = glm::scale( l_trans, glm::vec3( l_translationComponent->m_scale.getX(),
				l_translationComponent->m_scale.getY(),
				l_translationComponent->m_scale.getZ() ) );

			unsigned int l_transformLoc = glGetUniformLocation( m_shaderProgramID, "transform" );
			glUniformMatrix4fv( l_transformLoc, 1, GL_FALSE, glm::value_ptr( l_trans ) );

			glUseProgram( m_shaderProgramID );
			glBindVertexArray( l_renderComponent->m_mesh->getVAO_ID() );
			glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		}
	}
}

void RenderSystem::receiveEvent( component::Event* p_event ) {}