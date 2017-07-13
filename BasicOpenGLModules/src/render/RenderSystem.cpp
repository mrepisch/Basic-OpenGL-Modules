
// External includes
#include <vector>
#include<glew\GL\glew.h>

// Internal includes
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "../component/Entity.h"
#include "../component/TranslationComponent.h"
#include "../component/EntityCollection.h"

using namespace render;
using namespace component;


RenderSystem::RenderSystem() : System( e_renderSystem)
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::update()
{
	std::vector<Entity*>l_entitys = EntityCollection::Instance().getEntityWithComponents( e_renderComponent );
	for (int i = 0; i < l_entitys.size(); ++i)
	{
		RenderComponent* a_renderComponent = ( RenderComponent*) l_entitys[ i ]->getComponent( e_renderComponent );
		TranslationComponent* a_translationComponent = ( TranslationComponent* )l_entitys[ i ]->getComponent( e_translationComponent );
		if (a_renderComponent != nullptr && a_translationComponent != nullptr)
		{
			glScalef( a_translationComponent->m_scale.getX(), a_translationComponent->m_scale.getY(), a_translationComponent->m_scale.getZ() );
			glRotated( a_translationComponent->m_rotation.getX(), 1.0, 0.0, 0.0 );
			glRotated( a_translationComponent->m_rotation.getY(), 0.0, 1.0, 0.0 );
			glRotated( a_translationComponent->m_rotation.getZ(), 0.0, 0.0, 1.0 );
			glTranslatef( a_translationComponent->m_position.getX(), a_translationComponent->m_position.getY(), a_translationComponent->m_position.getZ() );
			if (a_renderComponent->m_mesh != nullptr)
			{
				glBindTexture( GL_TEXTURE_2D, a_renderComponent->m_mesh->getTextureID() );
				glBegin( GL_TRIANGLES );
				auto l_meshes = a_renderComponent->m_mesh->getFaces();
				for (auto l_iter = l_meshes.cbegin(); l_iter != l_meshes.cend(); ++l_iter)
				{
					glColor3f( 1.0f, 1.0f, 1.0f );
					glTexCoord2f( ( *l_iter )->vertcies[ 0 ].textureCords.getX(), ( *l_iter )->vertcies[ 0 ].textureCords.getY() );
					glVertex3f( ( *l_iter )->vertcies[ 0 ].position.getX(), ( *l_iter )->vertcies[ 0 ].position.getY(), ( *l_iter )->vertcies[ 0 ].position.getZ() );
					glTexCoord2f( ( *l_iter )->vertcies[ 1 ].textureCords.getX(), ( *l_iter )->vertcies[ 1 ].textureCords.getY() );
					glVertex3f( ( *l_iter )->vertcies[ 1 ].position.getX(), ( *l_iter )->vertcies[ 1 ].position.getY(), ( *l_iter )->vertcies[ 1 ].position.getZ() );
					glTexCoord2f( ( *l_iter )->vertcies[ 2 ].textureCords.getX(), ( *l_iter )->vertcies[ 2 ].textureCords.getY() );
					glVertex3f( ( *l_iter )->vertcies[ 2 ].position.getX(), ( *l_iter )->vertcies[ 2 ].position.getY(), ( *l_iter )->vertcies[ 2 ].position.getZ() );
				}
				glEnd();
			}
		}
	}
}

void RenderSystem::receiveEvent( component::Event* p_event ) {}