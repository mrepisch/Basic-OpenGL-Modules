#pragma once

// Internal includes
#include "Component.h"

#include <util\Vector3D.h>
namespace component
{
	class TranslationComponent : public Component
	{
	public:
		TranslationComponent( void );
		util::VectorF m_position;
		util::VectorF m_rotation;
		util::VectorF m_scale;
	};
}