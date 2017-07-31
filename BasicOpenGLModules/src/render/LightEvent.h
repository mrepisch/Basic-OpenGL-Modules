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
		util::VectorF m_newColor;
		util::VectorF m_newAmbient;
	};
}