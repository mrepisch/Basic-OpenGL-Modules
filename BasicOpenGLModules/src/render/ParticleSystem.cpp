// External includes
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Internal includes
#include "ParticleSystem.h"
#include "ParticelComponent.h"

using namespace render;
using namespace component;

ParticleSystem::ParticleSystem( core::ShaderManager* p_shader, EntityCollection* p_collection ) : System(e_partikelSystem, p_collection)
{
	m_shader = p_shader;
	srand( time( NULL ) );
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::update()
{
	std::vector<Entity*>l_particleSources = m_collection->getEntityWithComponents( e_particelComponent );
	for ( int i = 0; i < l_particleSources.size(); ++i )
	{
		ParticelComponent* l_particelComp = ( ParticelComponent* )l_particleSources[ i ]->getComponent( e_particelComponent );
		if( l_particelComp != nullptr)
		{
			if (l_particelComp->m_needInit)
			{
				l_particelComp->m_needInit = false;
				initParticelComponent( l_particelComp );
			}
			else
			{
				m_shader->useProgram( "particle" );
				glActiveTexture( GL_TEXTURE0 );
				glBindTexture( GL_TEXTURE_2D, l_particelComp->texturesMap[0]->getTextureID() ); // note: we also made the textures_loaded vector public (instead of private) from the model class.
				for (unsigned int i = 0; i < l_particelComp->particleMesh->getVertexCount(); i++)
				{
					glBindVertexArray( l_particelComp->particleMesh->getVAO_ID() );
					glDrawElementsInstanced( GL_TRIANGLES, l_particelComp->particleMesh->getFaces().size() * 3, GL_UNSIGNED_INT, 0, l_particelComp->particleCount );
					glBindVertexArray( 0 );
				}
			}
		}
	}
}


void ParticleSystem::receiveEvent( Event* p_event )
{

}


void ParticleSystem::initParticelComponent( ParticelComponent* p_comp )
{
	// Load Mesh
	for (int i = 0; i < p_comp->m_listOfTexturesPaths.size(); ++i)
	{
		p_comp->texturesMap.insert( std::make_pair( i, new Texture( p_comp->m_listOfTexturesPaths[ i ].c_str() ) ) );
	}

	if (p_comp->m_shape == e_quad)
	{
		Mesh* l_mesh = new Mesh();
		Vertex* l_vertex = new Vertex();
		l_vertex->position = util::VectorF(-0.5f,0.5f,0.0f);
		l_vertex->textureCords = util::VectorF( 0.0f, 0.0f, 0.0f );
		l_vertex->id = 0;
		l_mesh->addVertex( l_vertex );

		l_vertex = new Vertex();
		l_vertex->position = util::VectorF( 0.5f, 0.5f, 0.0f );
		l_vertex->textureCords = util::VectorF( 1.0f, 0.0f, 0.0f );
		l_vertex->id = 1;
		l_mesh->addVertex( l_vertex );

		l_vertex = new Vertex();
		l_vertex->position = util::VectorF( -0.5f, -0.5f, 0.0f );
		l_vertex->textureCords = util::VectorF( 0.0f, 1.0f, 0.0f );
		l_vertex->id = 2;
		l_mesh->addVertex( l_vertex );

		l_vertex = new Vertex();
		l_vertex->position = util::VectorF( 0.5f, -0.5f, 0.0f );
		l_vertex->textureCords = util::VectorF( 1.0f, 1.0f, 0.0f );
		l_vertex->id = 3;
		l_mesh->addVertex( l_vertex );

		Face* l_face = new Face();
		l_face->ID = 0;
		l_face->vertcies[ 0 ] = 0;
		l_face->vertcies[ 1 ] = 1;
		l_face->vertcies[ 2 ] = 2;
		l_mesh->addFace( l_face );

		l_face = new Face();
		l_face->ID = 1;
		l_face->vertcies[ 0 ] = 3;
		l_face->vertcies[ 1 ] = 2;
		l_face->vertcies[ 2 ] = 1;
		l_mesh->addFace( l_face );
		p_comp->particleMesh = l_mesh;
		unsigned int amount = p_comp->particleCount;
		glm::mat4 *modelMatrices;
		modelMatrices = new glm::mat4[ amount ];
		float radius = 50.0;
		float offset = 2.5f;
		for (unsigned int i = 0; i < amount; i++)
		{
			glm::mat4 model;
			// 1. translation: displace along circle with 'radius' in range [-offset, offset]
			float angle = ( float )i / ( float )amount * 360.0f;
			float displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float x = sin( angle ) * radius + displacement;
			displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
			displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float z = cos( angle ) * radius + displacement;
			model = glm::translate( model, glm::vec3( x, y, z ) );

			// 2. scale: Scale between 0.05 and 0.25f
			float scale = ( rand() % 20 ) / 100.0f + 0.05;
			model = glm::scale( model, glm::vec3( scale ) );

			// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
			float rotAngle = ( rand() % 360 );
			model = glm::rotate( model, rotAngle, glm::vec3( 0.4f, 0.6f, 0.8f ) );

			// 4. now add to list of matrices
			modelMatrices[ i ] = model;
		}

		p_comp->m_VAO = l_mesh->generateInstaciatetBuffer(20,modelMatrices);
	}

	
}

