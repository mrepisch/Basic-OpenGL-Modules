#pragma once
// External includes
#include <list>
#include <map>

// Internal includes
#include "../component/Component.h"
#include "../util/Vector3D.h"
#include "Texture.h"
#include "Mesh.h"

namespace render
{
	enum EnParticleShape
	{
		e_quad = 0,
		e_triangle
	};

	struct SParticle
	{
		int liftspanLeft = 0;
		util::VectorF dir;
		util::VectorF color;
		int textureID;
		Mesh* mesh;
	};

	class ParticelComponent : public component::Component
	{
	public:
		ParticelComponent();
		virtual ~ParticelComponent();

		void serialize( rapidxml::xml_node<>* p_rootNode );

		void deserialize( rapidxml::xml_node<>* p_componentNode );

		std::list<SParticle*>m_particels;

		int m_durotation;

		int m_timeLeft;

		unsigned int particleCount; 

		float particleScale;

		// How many frames does the particel life
		int particleLifeSpan;

		EnParticleShape m_shape;


		util::VectorF m_particleColor;

		std::map<int, Texture*>texturesMap;

		Mesh* particleMesh;

		bool m_needInit = true;

		GLuint m_VAO;

		std::vector<std::string>m_listOfTexturesPaths;

	};
}
