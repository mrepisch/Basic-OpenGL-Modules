#include "LightEvent.h"

using namespace render;
using namespace component;

LightEvent::LightEvent( long p_entityID ) :Event( e_lightEvent )
{
	m_entityID = p_entityID;;
	m_newColor.set( 1.0f, 1.0f, 1.0f );
	m_newAmbient.set( 0.0f, 0.0f, 0.0f );
}