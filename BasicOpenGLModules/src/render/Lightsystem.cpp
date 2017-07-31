
#include <vector>

#include "LightSystem.h"
#include "LightningComponent.h"
#include "LightEvent.h"
#include "../game/CameraComponent.h"
#include "../component/TranslationComponent.h"
#include "../render/RenderComponent.h"
using namespace render;
using namespace component;
using namespace game;
using namespace core;

Lightsystem::Lightsystem( EntityCollection* p_collection, ShaderManager* p_shaderManager, Entity* p_camera ) : System( e_lightningSystem, p_collection )
{
	m_shaderManager = p_shaderManager;
	m_camera = p_camera;
}

Lightsystem::~Lightsystem()
{

}




void Lightsystem::update()
{
	std::vector<Entity*>l_lights = m_collection->getEntityWithComponents( e_lightningComponent );
	int l_amountOfLights = l_lights.size();
	if (m_camera != nullptr)
	{
		CameraComponent* l_cameraComp = ( CameraComponent* )m_camera->getComponent( e_cameraComponent );
		if (l_cameraComp != nullptr)
		{
			for (int l_lightIndex = 0; l_lightIndex < l_lights.size(); ++l_lightIndex)
			{
				std::vector<Entity*>l_entitysToRender = m_collection->getEntityWithComponents( e_renderComponent );
				for (int l_entityIndex = 0; l_entityIndex < l_entitysToRender.size(); ++l_entityIndex)
				{
					RenderComponent* l_renderComp = (RenderComponent*) l_entitysToRender[ l_entityIndex ]->getComponent( e_renderComponent );
					LightningComponent* l_lightComp = ( LightningComponent* )l_lights[ l_lightIndex ]->getComponent( e_lightningComponent );
					if (l_renderComp != nullptr && l_lightComp != nullptr)
					{
						m_shaderManager->useProgram( l_renderComp->m_mesh->getShaderProgramNameName() );
						std::string l_uniformBase = "lightsource[" + l_lightIndex;
						l_uniformBase += "]";

						m_shaderManager->setInt( l_lightComp->m_type, l_uniformBase + ".type", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setInt( l_amountOfLights, "amountOfLights", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setVector( l_lightComp->m_lightColor.convertToGlmVec3(), l_uniformBase + ".lightColor",
							l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setVector( l_lightComp->m_ambient.convertToGlmVec3(), l_uniformBase + ".ambient",
							l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setVector( l_lightComp->m_direction.convertToGlmVec3(), l_uniformBase + ".direction",
							l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setVector( l_lightComp->m_position.convertToGlmVec3(), l_uniformBase + ".position",
							l_renderComp->m_mesh->getShaderProgramNameName() );
						
						m_shaderManager->setFloat( l_lightComp->m_constant, l_uniformBase + ".constant", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setFloat( l_lightComp->m_linear, l_uniformBase + ".linear", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setFloat( l_lightComp->m_quadratic, l_uniformBase + ".quadratic", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setFloat( l_lightComp->m_cutOff, l_uniformBase + ".m_cutOff", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setFloat( l_lightComp->m_cutOff, l_uniformBase + ".m_cutOff", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setFloat( l_lightComp->m_outCutOff, l_uniformBase + ".outerCutOff", l_renderComp->m_mesh->getShaderProgramNameName() );
						m_shaderManager->setVector( l_cameraComp->m_pos, "viewPos", l_renderComp->m_mesh->getShaderProgramNameName() );
					}
				}
			}
		}
	}
}


void Lightsystem::setCamera( Entity* p_entity )
{
	m_camera = p_entity;
}


void Lightsystem::receiveEvent( Event* p_event )
{
	if (p_event->getEventType() == e_lightEvent)
	{
		LightEvent* l_event = ( LightEvent* )p_event;
		if (l_event != nullptr)
		{
			Entity* l_entity = m_collection->getEntityByID( l_event->m_entityID );
			LightningComponent* a_comp =( LightningComponent*)( l_entity->getComponent( e_lightningComponent ) );
			if (a_comp != nullptr)
			{
				a_comp->m_lightColor = l_event->m_newColor;
				a_comp->m_ambient = l_event->m_newAmbient;
			}
		}
	}
	
}
