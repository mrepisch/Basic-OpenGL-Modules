#pragma once

#include "../component/Event.h"
#include "../util/Vector3D.h"
namespace render
{
	class LightEvent : public component::Event
	{
	public:
		LightEvent( long p_entitiyID );
		~LightEvent() {};

		long m_entityID;
		util::VectorF lightColorToAdd;
		util::VectorF ambientToAdd;
		// used for e_directionalLift
		util::VectorF newDirection;
		util::VectorF positionToAdd;

		util::VectorF specular;
		util::VectorF diffuse;
		// used for point light
		float constantToAdd;
		float linearToAdd;
		float quadraticToAdd;
		float outCutOffToAdd;
		// used for flashlight
		float cutOffToAdd;
	};
}