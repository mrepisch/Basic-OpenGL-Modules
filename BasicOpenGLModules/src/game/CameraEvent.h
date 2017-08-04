#pragma once

// Internal includes
#include "../component/Event.h"
#include "../util/Vector3D.h"

namespace game
{
	/**
	 * Event which is used to move and rotate the camera.
	 * This event will be processed in the CameraSystem
	 * @author sascha blank
	 */
	class CameraEvent : public component::Event
	{
	public:

		enum EnCamera_Movement
		{
			e_forward = 0,
			e_backward,
			e_left,
			e_right,
			e_none
		};


		/**
		 * Default constructor
		 * @author sascha blank
		 */
		CameraEvent( void );

		/**
		 * Virtual destructor
		 */
		virtual ~CameraEvent( void );

		/**
		 * Function to return the rotation offset to the current camera rotation
		 * @author sascha blank
		 * @return const VectorF& with the rotation offset
		 */
		const util::VectorF& getRotation() const;


		/**
		 * Sets the rotation offset to the current camera rotation
		 * @author sascha blank
		 * @param const VectorF&, the rotation offset
		 */
		void setRotation( const util::VectorF& p_rotation );

		float velocity;

		EnCamera_Movement direction;

	private	:

		// the rotation offset to the current camera rotation
		util::VectorF m_rotation;


	};
}