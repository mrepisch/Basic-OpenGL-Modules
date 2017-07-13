#pragma once

// Internal includes
#include "../component/Event.h"
#include "../util/Vector3D.h"

namespace game
{
	class CameraEvent : public component::Event
	{
	public:
		CameraEvent();
		virtual ~CameraEvent();
		const util::VectorF& getOffset() const;
		const util::VectorF& getRotation() const;

		void setOffset( const util::VectorF& p_offset );
		void setRotation( const util::VectorF& p_rotation );

	private:

		util::VectorF m_offset;
		util::VectorF m_rotation;

	};
}