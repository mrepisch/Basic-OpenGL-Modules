
// External includes
#include <vector>
#include<glew\GL\glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Internal includes
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "../component/TranslationComponent.h"
#include "../game/CameraComponent.h"

using namespace render;
using namespace component;
using namespace game;

RenderSystem::RenderSystem( EntityCollection* p_collection, core::ShaderManager* p_shaderManager ) : System( e_renderSystem, p_collection)
{
	
	m_shaderManager = p_shaderManager;
	m_camera =  m_collection->getEntityWithComponents( e_cameraComponent )[ 0 ];

}

RenderSystem::~RenderSystem()
{

}


void RenderSystem::update()
{
	glm::mat4 l_view;
	glm::mat4 l_projection;
	// handle camera
	CameraComponent* l_cameraComp = (CameraComponent*)(m_camera->getComponent( e_cameraComponent ) );
	if (l_cameraComp != nullptr)
	{
		l_projection = glm::perspective( glm::radians( 45.0f ), ( float )l_cameraComp->m_screenWidth / ( float )l_cameraComp->m_screenHeight, 0.1f, l_cameraComp->m_depth );
	}
	std::vector<Entity*>l_entitys = m_collection->getEntityWithComponents( e_renderComponent );
	for (int i = 0; i < l_entitys.size(); ++i)
	{
		RenderComponent* l_renderComponent = ( RenderComponent*) l_entitys[ i ]->getComponent( e_renderComponent );
		TranslationComponent* l_translationComponent = ( TranslationComponent* )l_entitys[ i ]->getComponent( e_translationComponent );
		if (l_renderComponent != nullptr && l_translationComponent != nullptr)
		{
			m_shaderManager->useProgram( l_renderComponent->m_mesh->getShaderProgramNameName() );

			// transform 
			glm::mat4 l_trans;
			l_trans = glm::translate( l_trans, glm::vec3( 
				l_translationComponent->m_position.getX(),
				l_translationComponent->m_position.getY(),
				l_translationComponent->m_position.getZ()
			));

			l_trans = glm::rotate( l_trans, l_translationComponent->m_rotation.getX(), glm::vec3( 1.0, 0.0, 0.0 ) );
			l_trans = glm::rotate( l_trans, l_translationComponent->m_rotation.getY(), glm::vec3( 0.0, 1.0, 0.0 ) );
			l_trans = glm::rotate( l_trans, l_translationComponent->m_rotation.getZ(), glm::vec3( 0.0, 0.0, 1.0 ) );


			l_trans = glm::scale( l_trans, glm::vec3( l_translationComponent->m_scale.getX(),
				l_translationComponent->m_scale.getY(),
				l_translationComponent->m_scale.getZ() ) );
			m_shaderManager->setMatrix( l_projection, "projection", l_renderComponent->m_mesh->getShaderProgramNameName() );
			m_shaderManager->setMatrix( l_cameraComp->getViewMatrix(), "view", l_renderComponent->m_mesh->getShaderProgramNameName() );
			m_shaderManager->setMatrix( l_trans, "transform", l_renderComponent->m_mesh->getShaderProgramNameName() );
			m_shaderManager->setFloat( 50.0f, "material.shininess", l_renderComponent->m_mesh->getShaderProgramNameName() );
			m_shaderManager->setVector( l_renderComponent->m_mesh->getMaterial()->diffuseColor.convertToGlmVec3(),
				"material.diffuseColor",
				l_renderComponent->m_mesh->getShaderProgramNameName() );
			m_shaderManager->setVector( l_renderComponent->m_mesh->getMaterial()->specularColor.convertToGlmVec3(),
				"material.specular",
				l_renderComponent->m_mesh->getShaderProgramNameName() );

			if (l_renderComponent->m_mesh->getMaterial()->diffuseTexture != nullptr)
			{
				m_shaderManager->setInt( 0, "material.diffuseTexture", l_renderComponent->m_mesh->getShaderProgramNameName() );
				glActiveTexture( GL_TEXTURE0 );
				glBindTexture( GL_TEXTURE_2D, l_renderComponent->m_mesh->getMaterial()->diffuseTextureID );
			}
			if (l_renderComponent->m_mesh->getMaterial()->specularTexture != nullptr)
			{
				m_shaderManager->setInt( 1, "material.specularTexture", l_renderComponent->m_mesh->getShaderProgramNameName() );
				glActiveTexture( GL_TEXTURE1 );
				glBindTexture( GL_TEXTURE_2D, l_renderComponent->m_mesh->getMaterial()->specularTextureID );
			}
			glBindVertexArray( l_renderComponent->m_mesh->getVAO_ID() );
			glDrawElements( GL_TRIANGLES, (GLsizei)(l_renderComponent->m_mesh->getVertexCount()), GL_UNSIGNED_INT, 0 );
		}
	}
}

void RenderSystem::receiveEvent( component::Event* p_event ) {}