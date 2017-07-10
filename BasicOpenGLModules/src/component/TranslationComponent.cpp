#include "TranslationComponent.h"


using namespace component;

TranslationComponent::TranslationComponent(void) :Component(e_positionComponent)
{
	m_position.set(0.0f, 0.0f, 0.0f);
	m_scale.set(0.0f, 0.0f, 0.0f);
	m_rotation.set(0.0f, 0.0f, 0.0f);
}