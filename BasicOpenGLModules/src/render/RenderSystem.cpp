
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
		RenderComponent* l_renderComponent = ( RenderComponent*) l_entitys[ i ]->getComponent( e_renderComponent );
		TranslationComponent* l_translationComponent = ( TranslationComponent* )l_entitys[ i ]->getComponent( e_translationComponent );
		if (l_renderComponent != nullptr && l_translationComponent != nullptr)
		{
			glScalef( l_translationComponent->m_scale.getX(), l_translationComponent->m_scale.getY(), l_translationComponent->m_scale.getZ() );
			glRotated( l_translationComponent->m_rotation.getX(), 1.0, 0.0, 0.0 );
			glRotated( l_translationComponent->m_rotation.getY(), 0.0, 1.0, 0.0 );
			glRotated( l_translationComponent->m_rotation.getZ(), 0.0, 0.0, 1.0 );
			glTranslatef( l_translationComponent->m_position.getX(), l_translationComponent->m_position.getY(), l_translationComponent->m_position.getZ() );
			if (l_renderComponent->m_mesh != nullptr)
			{
				if (l_renderComponent->m_mesh->hasTexture())
				{
					glBindTexture( GL_TEXTURE_2D, l_renderComponent->m_mesh->getTextureID() );
					glEnableClientState( GL_VERTEX_ARRAY );
					glEnableClientState( GL_TEXTURE_COORD_ARRAY );
					glBindBuffer( GL_ARRAY_BUFFER, l_renderComponent->m_mesh->getVertexBufferID() );
					glColor3f( 1.0f, 1.0f, 1.0f );
					glTexCoordPointer( 2, GL_FLOAT, sizeof( float ) * 5, ( GLvoid* )( 3 * sizeof( float ) ) );
					glVertexPointer( 3, GL_FLOAT, sizeof( float ) * 5, ( GLvoid* )0 );
					glDrawArrays( GL_TRIANGLES, 0, (GLsizei)( l_renderComponent->m_mesh->getVertexCount() ));
					glDisableClientState( GL_TEXTURE_COORD_ARRAY );
					glDisableClientState( GL_VERTEX_ARRAY );
				}
				else
				{
					glEnableClientState( GL_VERTEX_ARRAY );
					glBindBuffer( GL_ARRAY_BUFFER, l_renderComponent->m_mesh->getVertexBufferID() );
					glColor3f( 1.0f, 1.0f, 1.0f );
					glVertexPointer( 3, GL_FLOAT, sizeof( float ) * 5, ( GLvoid* )0 );
					glDrawArrays( GL_TRIANGLES, 0, l_renderComponent->m_mesh->getVertexCount() );
					glDisableClientState( GL_VERTEX_ARRAY );
				}

			}
		}
	}
}

void RenderSystem::receiveEvent( component::Event* p_event ) {}