
// Externer includes
#include <vector>
#include <glew\GL\glew.h>

// Internal includes
#include "TranslationSystem.h"
#include "TranslationComponent.h"
#include "Entity.h"
#include "EntityCollection.h"
using namespace component;

TranslationSystem::TranslationSystem() :System(e_translationSystem)
{

}


void TranslationSystem::update()
{
	
}


void TranslationSystem::receiveEvent( Event* p_event )
{

}