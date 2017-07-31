#pragma once

// External includes
#include <string>
#include <rapidXml\rapidxml.hpp>
// Internal includes
#include "../render/Mesh.h"
#include "../util/Vector3D.h"

namespace util
{
	class BGLMeshLoader
	{
	public:
		BGLMeshLoader();
		virtual ~BGLMeshLoader();

		render::Mesh* loadMesh( const std::string& p_filename );
	private:
		void readVertecisNode( rapidxml::xml_node<>* p_vertexNode, render::Mesh* p_mesh );
		void readFacesNode( rapidxml::xml_node<>* p_facesNode, render::Mesh* p_mesh );
		util::VectorF readXYZAttributes( rapidxml::xml_node<>* p_node );
		util::VectorF readUVattributes( rapidxml::xml_node<>* p_node );
		void readIndicesAttributes( rapidxml::xml_node<>* p_node, render::Face* p_face );
		void readMaterial( rapidxml::xml_node<>* p_node, render::Mesh* p_mesh );
		util::VectorF readColorNode( rapidxml::xml_node<>* p_node );

	};
}