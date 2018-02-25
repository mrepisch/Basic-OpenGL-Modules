#pragma once
#include "../component/System.h"
#include "../core/ShaderManager.h"
#include "../component/Entity.h"

namespace render
{
	class Lightsystem : public component::System
	{

	public:

		Lightsystem( component::EntityCollection* p_collection, core::ShaderManager* p_shaderManager);
		virtual ~Lightsystem();

		void setCamera( component::Entity* p_entity );

		void update();


		/**
		* Function to received messages which are send by the MessagesDispatcher.
		* @author sascha blank
		* @param Event*, pointer on the event object
		*/
		void receiveEvent( component::Event* p_event );

	private:
		core::ShaderManager* m_shaderManager;
		component::Entity* m_camera;

	};
}
