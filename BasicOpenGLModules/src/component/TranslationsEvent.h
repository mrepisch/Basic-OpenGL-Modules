#pragma once
#include "Event.h"
#include "../util/Vector3D.h"

namespace component
{
	class TranslationsEvent : public Event
	{
	public:
		TranslationsEvent( long p_entityID);
		virtual ~TranslationsEvent();

		long m_entityID;
		util::VectorF m_positionsOffset;
		util::VectorF m_rotationOffset;
		util::VectorF m_scaleToAdd;
	};
}