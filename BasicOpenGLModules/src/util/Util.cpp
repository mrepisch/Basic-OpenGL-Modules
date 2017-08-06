
// External includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <direct.h>

// Internal includes
#include "Util.h"

using namespace std;
using namespace util;
using namespace rapidxml;


StringVec Util::SplitWithWiteSpace( std::string& t_toSplit)
{
	
	StringVec r_result;

	std::istringstream iss(t_toSplit);
	for (std::string s; iss >> s; )
		r_result.push_back(s);
	return r_result;
} 



std::string Util::readFile( const char* p_filename )
{
	string r_data;
	std::ifstream file( p_filename );
	std::string str;
	while (std::getline( file, str ))
	{
		r_data += str + "\n";
	}
	file.close();
	return r_data;
}


std::string Util::getBasePath( void )
{
	char *path = NULL;
	path = getcwd( NULL, 0 ); // or _getcwd
	std::string workingDir = path;
	return workingDir;
}


void Util::writeVectorToXmlNode( const VectorF& p_vector, const std::string& p_tagname, rapidxml::xml_node<>* p_node )
{
	xml_document<>* l_doc = p_node->document();
	std::string* l_tagName = new std::string( p_tagname );
	xml_node<>* l_vectorNode = l_doc->allocate_node( node_element, l_tagName->c_str() );
	p_node->append_node( l_vectorNode );

	std::string* a_xStr = new std::string( std::to_string( p_vector.getX() ) );
	std::string* a_yStr = new std::string( std::to_string( p_vector.getY() ) );
	std::string* a_zStr = new std::string( std::to_string( p_vector.getZ() ) );

	l_vectorNode->append_attribute( l_doc->allocate_attribute( "x", a_xStr->c_str() ) );
	l_vectorNode->append_attribute( l_doc->allocate_attribute( "y", a_yStr->c_str() ) );
	l_vectorNode->append_attribute( l_doc->allocate_attribute( "z", a_zStr->c_str() ) );

}


void Util::writeGLMVectorToXmlNode( const glm::vec3& p_vector, const std::string& p_tagname, rapidxml::xml_node<>* p_node )
{
	xml_document<>* l_doc = p_node->document();
	std::string* l_tagName = new std::string( p_tagname );
	xml_node<>* l_vectorNode = l_doc->allocate_node( node_element, l_tagName->c_str() );
	p_node->append_node( l_vectorNode );
	std::string* a_xStr = new std::string( std::to_string( p_vector.x ) );
	std::string* a_yStr = new std::string( std::to_string( p_vector.y ) );
	std::string* a_zStr = new std::string( std::to_string( p_vector.z ) );

	l_vectorNode->append_attribute( l_doc->allocate_attribute( "x", a_xStr->c_str() ) );
	l_vectorNode->append_attribute( l_doc->allocate_attribute( "y", a_yStr->c_str() ) );
	l_vectorNode->append_attribute( l_doc->allocate_attribute( "z", a_zStr->c_str() ) );

}

void Util::writeFloatAsAttributeToXmlNode( float p_value, const std::string& p_attributName, rapidxml::xml_node<>* p_node )
{
	xml_document<>* l_doc = p_node->document();
	std::string* a_floatStr = new std::string( std::to_string( p_value ) );
	std::string* l_attributName = new std::string( p_attributName );
	p_node->append_attribute( l_doc->allocate_attribute( l_attributName->c_str(), a_floatStr->c_str() ) );
}

VectorF Util::readVectorFromXmlNode( xml_node<>*p_node )
{
	VectorF r_vector;
	r_vector.setX( std::stof( p_node->first_attribute( "x" )->value() ) );
	r_vector.setY( std::stof( p_node->first_attribute( "y" )->value() ) );
	r_vector.setZ( std::stof( p_node->first_attribute( "z" )->value() ) );
	return r_vector;
}

glm::vec3 Util::readGLMVectorFromXmlNode( xml_node<>* p_node )
{
	glm::vec3 r_vec;
	r_vec.x = std::stof( p_node->first_attribute( "x" )->value());
	r_vec.y = std::stof( p_node->first_attribute( "y" )->value());
	r_vec.z = std::stof( p_node->first_attribute( "z" )->value());
	return r_vec;
}

float Util::readFloatFromAttribute( xml_node<>* p_node, const std::string& p_attributeName )
{
	float r_value = std::stof( p_node->first_attribute( p_attributeName.c_str() )->value() );
	return r_value;
}