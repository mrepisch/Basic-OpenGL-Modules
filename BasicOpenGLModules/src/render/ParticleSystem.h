#pragma once

#include "../component/System.h"
#include "../core/ShaderManager.h"
namespace render
{
	class ParticelComponent;
	class ParticleSystem : public component::System
	{
	public:
		ParticleSystem(core::ShaderManager* p_shader, component::EntityCollection* p_collection);
		virtual ~ParticleSystem();

		void update();

		void receiveEvent( component::Event* p_event );

	private:

		void initParticelComponent( ParticelComponent* p_comp );
		core::ShaderManager* m_shader;
	};
}