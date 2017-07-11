
// Externer includes
#include <vector>
#include <glew\GL\glew.h>

// Internal includes
#include "TranslationSystem.h"
#include "TranslationComponent.h"
#include "Entity.h"

using namespace component;

TranslationSystem::TranslationSystem() :System(e_translationSystem)
{

}

void TranslationSystem::update()
{
	std::vector<Entity*>a_entitys = m_entityCollection->getEntityWithComponents(e_translationComponent);
	for (int i = 0; i < a_entitys.size(); ++i)
	{
		Entity* a_entity = a_entitys[i];
		TranslationComponent* a_comp = (TranslationComponent*)( a_entity->getComponent(e_translationComponent) );
		glScalef(a_comp->m_scale.getX(), a_comp->m_scale.getY(), a_comp->m_scale.getZ());
		glRotated(a_comp->m_rotation.getX(), 1.0, 0.0, 0.0);
		glRotated(a_comp->m_rotation.getY(), 0.0, 1.0, 0.0);
		glRotated(a_comp->m_rotation.getZ(), 0.0, 0.0, 1.0);
		glTranslatef(a_comp->m_position.getX(), a_comp->m_position.getY(), a_comp->m_position.getZ());
	}
}