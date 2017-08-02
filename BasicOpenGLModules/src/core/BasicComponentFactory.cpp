#include "BasicComponentFactory.h"
#include "../game/CameraComponent.h"
#include "../render/RenderComponent.h"
#include "../component/TranslationComponent.h"
#include "../util/PLYParser.h"
#include "../render/Mesh.h"
#include "../render/LightningComponent.h"
#include "../util/BGLMeshLoader.h"
#include "../render/CubeMapComponent.h"

using namespace core;
using namespace component;
using namespace game;
using namespace render;

BasicComponentFactory::BasicComponentFactory( ShaderManager* p_shaderManager )
{
	m_shaderManager = p_shaderManager;
}


Component* BasicComponentFactory::generateComponentFromVector( const std::vector<std::string>& p_data )
{

	Component* r_comp = nullptr;
	if (p_data[ 0 ] == "render")
	{
		util::BGLMeshLoader l_parser;
		Mesh* l_mesh = l_parser.loadMesh( p_data[ 1 ] );
		l_mesh->setShaderProgramName( p_data[ 2 ] );
		l_mesh->generateBuffer();
		return new RenderComponent( l_mesh );
	}
	else if (p_data[ 0 ] == "light")
	{
		std::string l_shaderProgram = p_data[ 1 ];
		return new LightningComponent( ( EnLightType ) std::atoi(p_data[2].c_str()),l_shaderProgram );
	}
	else if (p_data[ 0 ] == "cubemap")
	{
		CubeMapComponent* a_comp = new CubeMapComponent();
		util::BGLMeshLoader l_parser;
		a_comp->skyboxMesh = l_parser.loadMesh( p_data[ 1 ] );
		a_comp->skyboxMesh->setShaderProgramName( p_data[ 2 ] );
		a_comp->skyboxMesh->generateBuffer();
		a_comp->m_shaderID = m_shaderManager->getShaderProgramID( p_data[ 2 ] );
		std::vector<std::string>l_textures;
		l_textures.push_back( p_data[ 3 ] );
		l_textures.push_back( p_data[ 4 ] );
		l_textures.push_back( p_data[ 5 ] );
		l_textures.push_back( p_data[ 6 ] );
		l_textures.push_back( p_data[ 7 ] );
		l_textures.push_back( p_data[ 8 ] );

		a_comp->m_texture = new CubeMapTexture( l_textures );
		return a_comp;
	}
	return r_comp;
}


Component* BasicComponentFactory::generateComponentFromMap( const std::map<std::string, std::string>& p_data )
{
	Component* r_comp = nullptr;
	return r_comp;
}

Component* BasicComponentFactory::generateComponentFromString( const std::string& t_data )
{
	Component* r_comp = nullptr;
	if (t_data == "camera")
	{
		r_comp = new CameraComponent(800,600,1000.0f);
	}
	else if (t_data == "translation")
	{
		r_comp = new TranslationComponent();
	}

	return r_comp;
}