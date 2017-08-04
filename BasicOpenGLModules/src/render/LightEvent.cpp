#include "LightEvent.h"

using namespace render;
using namespace component;

LightEvent::LightEvent( long p_entityID ) :Event( e_lightEvent )
{
	m_entityID = p_entityID;
	lightColorToAdd.set( 0.0f, 0.0f, 0.0f );
	ambientToAdd.set( 0.0f, 0.0f, 0.0f );
	positionToAdd.set( 0.0f, 0.0f, 0.0f );
	newDirection.set( 0.0f, 0.0f, 0.0f );
	specular.set( 0.0f, 0.0f, 0.0f );
	diffuse.set( 0.0f, 0.0f, 0.0f );
	constantToAdd = 0;
	linearToAdd = 0;
	quadraticToAdd = 0;
	outCutOffToAdd = 0;
	cutOffToAdd = 0;
}