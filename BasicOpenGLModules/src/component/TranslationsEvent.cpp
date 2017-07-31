#include "TranslationsEvent.h"

using namespace component;

TranslationsEvent::TranslationsEvent(long p_entityID) : Event( e_translationEvent )
{
	m_positionsOffset.set( 0.0f, 0.0f, 0.0 );
	m_rotationOffset.set( 0.0f, 0.0f, 0.0 );
	m_scaleToAdd.set( 0.0f, 0.0f, 0.0 );
	m_entityID = p_entityID;
}

TranslationsEvent::~TranslationsEvent()
{

}