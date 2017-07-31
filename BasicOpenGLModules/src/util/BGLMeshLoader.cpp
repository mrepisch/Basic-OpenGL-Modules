

#include <iostream>
#include<string>

#include "BGLMeshLoader.h"
#include <sstream>
#include <fstream>

#include <streambuf>

#include "Util.h"


using namespace util;
using namespace render;
using namespace rapidxml;

const std::string S_BASEPATHTEXTURES = Util::getBasePath() + "/textures/";
const std::string S_BASEPATHMODELS = Util::getBasePath() +  "/models/";

BGLMeshLoader::BGLMeshLoader()
{

}

BGLMeshLoader::~BGLMeshLoader()
{

}


Mesh* BGLMeshLoader::loadMesh( const std::string& p_filename )
{


	std::string buffer;
	std::string line;
	std::string a_test = S_BASEPATHMODELS + p_filename;
	std::ifstream xml_file(S_BASEPATHMODELS + p_filename );
	if (xml_file.is_open())
	{
		while (xml_file.good())
		{
			getline( xml_file, line );
			buffer += line;
		}
		xml_file.close();
	}
	else
	{
		std::cout << "ERROR: xml file not found " << p_filename << std::endl;
	}

	//Create a char buffer
	char *pbuffer = new char[ buffer.length() + 1 ];
	strcpy_s( pbuffer, sizeof(char)*buffer.length() + 1,buffer.c_str() );
	pbuffer[ buffer.length() ] = '\0';
	xml_document<> doc;
	// create new mesh
	Mesh* r_mesh = new Mesh();
	doc.parse<0>( pbuffer );
	xml_node<>*meshNode = doc.first_node( "mesh" );
	for (auto meshChild = meshNode->first_node(); meshChild; meshChild = meshChild->next_sibling())
	{
		std::cout << meshChild->name() << std::endl;
		if (std::string( meshChild->name()) == "materials")
		{
			readMaterial( meshChild, r_mesh );
		}
		else if (std::string( meshChild->name() ) == "uv_layer")
		{

		}
		else if (std::string(meshChild->name()) == "vertices")
		{
			readVertecisNode( meshChild, r_mesh );
		}
		else if (std::string( meshChild->name() ) == "faces")
		{
			readFacesNode( meshChild, r_mesh );
		}
	}
	return r_mesh;
}


void BGLMeshLoader::readVertecisNode( rapidxml::xml_node<>* p_vertexNode, render::Mesh* p_mesh )
{
	for (auto vertexNode = p_vertexNode->first_node( "vertex" ); vertexNode; vertexNode = vertexNode->next_sibling())
	{
		Vertex* vertex = new Vertex();
		xml_node<>* positionNode = vertexNode->first_node( "position" );
		vertex->position = readXYZAttributes( positionNode );
		vertex->normal = readXYZAttributes( vertexNode->first_node( "normal" ) );
		vertex->textureCords = readUVattributes( vertexNode->first_node( "textcord" ) );
		p_mesh->addVertex( vertex );
	}
	
}


VectorF BGLMeshLoader::readXYZAttributes( xml_node<>* p_node )
{
	VectorF r_vec;
	r_vec.setX( std::stof( p_node->first_attribute( "x" )->value() ) );
	r_vec.setY( std::stof( p_node->first_attribute( "z" )->value() ) );
	r_vec.setZ( std::stof( p_node->first_attribute( "y" )->value() ) );
	return r_vec;
}


VectorF BGLMeshLoader::readUVattributes( xml_node<>* p_node )
{
	VectorF r_vec;
	r_vec.setX( std::stof( p_node->first_attribute( "u" )->value() ) );
	r_vec.setY( std::stof( p_node->first_attribute( "v" )->value() ) );
	r_vec.setZ( 0.0f );
	return r_vec;
}


void BGLMeshLoader::readFacesNode( rapidxml::xml_node<>* p_facesNode, render::Mesh* p_mesh )
{
	for (auto faceNode = p_facesNode->first_node( "face" ); faceNode; faceNode = faceNode->next_sibling())
	{
		Face* face = new Face();
		readIndicesAttributes( faceNode, face );
		xml_node<>* normalNode = faceNode->first_node( "normal" );
		//face->normal = readXYZAttributes( normalNode );
		p_mesh->addFace( face );
	}
}


void BGLMeshLoader::readIndicesAttributes( rapidxml::xml_node<>* p_node, render::Face* p_face )
{
	p_face->vertcies[ 0 ] = std::atoi( p_node->first_attribute( "v1" )->value() );
	p_face->vertcies[ 1 ] = std::atoi( p_node->first_attribute( "v2" )->value() );
	p_face->vertcies[ 2 ] = std::atoi( p_node->first_attribute( "v3" )->value() );
	p_face->ID = std::atoi( p_node->first_attribute( "id" )->value() );
	p_face->materialID = std::atoi( p_node->first_attribute( "material" )->value() ) ;
	std::string a_temp = p_node->first_attribute( "smooth" )->value();
	if (a_temp == "true")
	{
		p_face->smooth = true;
	}
	else
	{
		p_face->smooth = false;
	}
}


void BGLMeshLoader::readMaterial( rapidxml::xml_node<>* p_node, render::Mesh* p_mesh )
{
	for (auto materialNode = p_node->first_node( "p_material" ); materialNode; materialNode = materialNode->next_sibling())
	{
		Material* material = new Material();
		material->diffuseColor = readColorNode( materialNode->first_node( "diffuse" )->first_node( "color" ) );
		material->specularColor = readColorNode( materialNode->first_node( "specular" )->first_node( "color" ) );
		material->ID = std::atoi( materialNode->first_attribute( "id" )->value() );
		//material->texturePath = materialNode->first_node( "textureset" )->first_node( "texture_slot" )->first_node( "image" )->first_attribute( "url" )->value();
		int l_textureCounter = 0;
		for (xml_node<>* l_texutreSlotNode = materialNode->first_node( "textureset" )->first_node( "texture_slot" ); l_texutreSlotNode; l_texutreSlotNode = l_texutreSlotNode->next_sibling())
		{
			if (l_textureCounter == 0)
			{
				std::string l_diffuseTexturePath = l_texutreSlotNode->first_node( "image" )->first_attribute( "url" )->value();
				material->diffuseTexture = new Texture( (S_BASEPATHTEXTURES + l_diffuseTexturePath).c_str()  );
				material->diffuseTextureID = material->diffuseTexture->getTextureID();
			}
			else if (l_textureCounter == 1)
			{
				std::string l_specularTexutrePath = l_texutreSlotNode->first_node( "image" )->first_attribute( "url" )->value();
				material->specularTexture = new Texture( ( S_BASEPATHTEXTURES + l_specularTexutrePath).c_str() );
				material->specularTextureID = material->specularTexture->getTextureID();
			}
			++l_textureCounter;
		}
		if (material->specularTexture == nullptr)
		{
			material->specularTexture = material->diffuseTexture;
		}
		p_mesh->setMaterial( material );
	}
}


VectorF BGLMeshLoader::readColorNode( rapidxml::xml_node<>* p_node )
{
	VectorF r_vec;
	r_vec.set( std::stof( p_node->first_attribute( "r" )->value() ),
		std::stof( p_node->first_attribute( "g" )->value() ),
		std::stof( p_node->first_attribute( "b" )->value() ) );
	return r_vec;
}

