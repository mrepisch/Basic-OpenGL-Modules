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
		 * Returns the offset to the current camera position
		 * @author sascha blank
		 * @return const VectorF& with the offset
		 */
		const util::VectorF& getOffset() const;

		/**
		 * Function to return the rotation offset to the current camera rotation
		 * @author sascha blank
		 * @return const VectorF& with the rotation offset
		 */
		const util::VectorF& getRotation() const;

		/**
		 * Sets the offset to the current camera position
		 * @author sascha blank
		 * @param const VectorF&, the camera offset
		 */
		void setOffset( const util::VectorF& p_offset );

		/**
		 * Sets the rotation offset to the current camera rotation
		 * @author sascha blank
		 * @param const VectorF&, the rotation offset
		 */
		void setRotation( const util::VectorF& p_rotation );

	private	:

		// The offset to the current camera position
		util::VectorF m_offset;

		// the rotation offset to the current camera rotation
		util::VectorF m_rotation;
	};
}