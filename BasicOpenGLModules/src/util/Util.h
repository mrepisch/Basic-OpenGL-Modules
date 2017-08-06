#pragma once

#include <vector>
#include <string>
#include <rapidXml\rapidxml.hpp>
#include <glm/glm.hpp>
#include "Vector3D.h"
namespace util
{
	typedef std::vector<std::string> StringVec;

	class Util
	{
	public:
		static StringVec SplitWithWiteSpace(std::string& t_split);

		static std::string readFile( const char* p_filename );

		static std::string getBasePath( void );

		static void writeVectorToXmlNode( const VectorF& p_vector, const std::string& p_tagname, rapidxml::xml_node<>* p_node );

		static void writeGLMVectorToXmlNode( const glm::vec3& p_vector, const std::string& p_tagname, rapidxml::xml_node<>* p_node );

		static void writeFloatAsAttributeToXmlNode( float p_value, const std::string& p_attributName, rapidxml::xml_node<>* p_node );

		static VectorF readVectorFromXmlNode( rapidxml::xml_node<>*p_node );

		static glm::vec3 readGLMVectorFromXmlNode( rapidxml::xml_node<>* p_node );

		static float readFloatFromAttribute( rapidxml::xml_node<>* p_node, const std::string& p_attributeName );

	};
}


