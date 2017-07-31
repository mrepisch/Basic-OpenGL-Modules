
// Externer includes
#include <vector>
#include <glew\GL\glew.h>

// Internal includes
#include "TranslationSystem.h"
#include "TranslationComponent.h"
#include "TranslationsEvent.h"
#include "Entity.h"
#include "EntityCollection.h"
#include "../util/Vector3D.h"
using namespace component;

TranslationSystem::TranslationSystem( EntityCollection* p_collection) : System(e_translationSystem, p_collection )
{

}


void TranslationSystem::update()
{
	/*std::vector<Entity*> a_ents = m_collection->getEntityWithComponents( e_translationComponent );
	TranslationComponent* a_comp = (TranslationComponent*)a_ents[ 0 ]->getComponent( e_translationComponent );
	if (a_comp != nullptr)
	{
		a_comp->m_rotation = a_comp->m_rotation + util::VectorF( 0.01f, 0.01f, 0.01f );
	}*/
}


void TranslationSystem::receiveEvent( Event* p_event )
{
	if (p_event->getEventType() == e_translationEvent)
	{
		TranslationsEvent* l_event = ( TranslationsEvent* )( p_event );
		if (l_event != nullptr)
		{
			Entity* l_entitiy = m_collection->getEntityByID( l_event->m_entityID );
			if (l_entitiy != nullptr)
			{
				TranslationComponent* a_comp = ( TranslationComponent*)( l_entitiy->getComponent( e_translationComponent ) );
				if (a_comp != nullptr)
				{
					a_comp->m_position = a_comp->m_position + l_event->m_positionsOffset;
					a_comp->m_rotation = a_comp->m_rotation + l_event->m_rotationOffset;
					a_comp->m_scale = a_comp->m_scale + l_event->m_scaleToAdd;
				}

			}
		}

	}
}