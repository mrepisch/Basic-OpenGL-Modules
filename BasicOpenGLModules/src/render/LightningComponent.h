#pragma once

// External includes
#include <string>

// Internal includes
#include "../component/Component.h"
#include "../util/Vector3D.h"

namespace render
{
	enum EnLightType
	{
		e_directionalLight = 0,
		e_pointLight,
		e_flashLight
	};

	class LightningComponent : public component::Component
	{
	public:

		LightningComponent(EnLightType p_type, const std::string& p_shaderName );
		virtual ~LightningComponent();

		EnLightType m_type;
		std::string m_shaderName;

		// used for e_lightSourcePoint
		util::VectorF m_lightColor;
		util::VectorF m_ambient;
		// used for e_directionalLift
		util::VectorF m_direction;
		util::VectorF m_position;
		util::VectorF m_specular;
		util::VectorF m_diffuse;
		// used for point light
		float m_constant;
		float m_linear;
		float m_quadratic;
		float m_outCutOff;
		// used for flashlight
		float m_cutOff;

		void serialize( rapidxml::xml_node<>* p_rootNode ) {}

	};
}