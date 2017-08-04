#include "LightningComponent.h"


using namespace render;
using namespace component;

LightningComponent::LightningComponent( EnLightType p_type, const std::string& p_shaderName ) : Component( e_lightningComponent )
{
	m_type = p_type;
	m_lightColor.set( 0.75f, 0.75f,0.75f );
	m_ambient.set( 0.0f, 0.0f, 0.0f );
	m_direction.set( 0.0f,0.0f,0.0f);
	m_position.set( 0.0f, 0.0f, 0.0f );
	m_specular.set( 0.0f, 0.0f, 0.0f );
	m_diffuse.set( 0.0f, 0.0f, 0.0f );
	m_constant = 1.0f;
	m_linear = 0.05f;
	m_quadratic = 0.012f;
	m_cutOff = 0.2f;
	m_outCutOff = 0.8f;
	m_shaderName = p_shaderName;
}

LightningComponent::~LightningComponent()
{

}