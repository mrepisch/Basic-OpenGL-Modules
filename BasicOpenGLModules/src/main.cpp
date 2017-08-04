#include <iostream>
#include <glew\GL\glew.h>


#include "core/Display.h"
#include "util\Vector3D.h"
#include "render\RenderSystem.h"
#include "render\RenderComponent.h"
#include "component\TranslationComponent.h"
#include "util\PLYParser.h"
#include "game\InputSystem.h"
#include "game\CameraSystem.h"
#include "core/BasicKeyInput.h"
#include "game\CameraComponent.h"
#include "component\TranslationSystem.h"
#include "core\BasicComponentFactory.h"
#include "core\BasicOpenGLCore.h"
#include "core\ShaderManager.h"
#include "render\LightSystem.h"
#include "component\TranslationsEvent.h"
#include "component\EventDispatcher.h"
#include "util\BGLMeshLoader.h"
#include "render\LightEvent.h"
using namespace render;
using namespace component;
using namespace util;
using namespace game;
using namespace core;

int main(int argc, char **argv)
{
	Display l_mainWindow(800, 600, "OpenGL Window");
	l_mainWindow.setFPS( 30 );

	ShaderManager l_shaderManager;
	l_shaderManager.createShaderProgram( "basic" );
	l_shaderManager.addShader( "vertex",
		ShaderManager::e_vertex,
		"basic_vertex.txt",
		"basic" );
	l_shaderManager.addShader( "fragment",
		ShaderManager::e_fragment,
		"fragment_shader.c",
		"basic" );


	l_shaderManager.createShaderProgram( "lightsource" );
	l_shaderManager.addShader( "vertex",
		ShaderManager::e_vertex,
		"lightVertex.txt",
		"lightsource" );

	l_shaderManager.addShader( "fragment",
		ShaderManager::e_fragment,
		"lightFragment.txt",
		"lightsource" );

	l_shaderManager.createShaderProgram( "skybox" );
	l_shaderManager.addShader( "vertex", ShaderManager::e_vertex, "cubemapVert.c", "skybox" );
	l_shaderManager.addShader( "fragment", ShaderManager::e_fragment, "cubemapFrag.c", "skybox" );

	l_shaderManager.compile();



	BasicOpenGLCore l_core(&l_mainWindow,& l_shaderManager);
	BasicComponentFactory l_factory(&l_shaderManager);

	l_core.addComponentFactory("basic", &l_factory );
	long l_camID = l_core.createNewEntity( "camera" );
	l_core.addComponentToEntity( l_camID, "basic" ,"camera" );

	std::vector<std::string>l_compData;
	l_compData.push_back( "render" );
	l_compData.push_back( "terain1.xml" );
	l_compData.push_back( "basic" );

	long l_groundID = l_core.createNewEntity( "ground" );
	l_core.addComponentToEntity( l_groundID,"basic",l_compData );
	l_core.addComponentToEntity( l_groundID, "basic", "translation" );
	
	TranslationsEvent* l_transEventforGround = new TranslationsEvent( l_groundID );
	l_transEventforGround->m_positionsOffset.set( 0.0f, -2.0f, 0.0f );
	//l_transEventforGround->m_scaleToAdd.set( 5.0f, 0.0f, 5.0f );
	EventDispatcher::Instance().addEvent( l_transEventforGround );

	l_compData.clear();
	l_compData.push_back( "render" );
	l_compData.push_back( "sun.xml" );
	l_compData.push_back( "lightsource" );

	long l_pointLight = l_core.createNewEntity( "sun" );
	l_core.addComponentToEntity( l_pointLight, "basic", l_compData );
	l_compData.clear();
	l_core.addComponentToEntity( l_pointLight, "basic", "translation" );
	l_compData.clear();
	l_compData.push_back( "light" );
	l_compData.push_back( "lightsource" );
	l_compData.push_back( "1" );
	l_core.addComponentToEntity( l_pointLight, "basic", l_compData );

	TranslationsEvent* l_transEvent = new TranslationsEvent(l_pointLight);
	l_transEvent->m_positionsOffset.set( 0.0f, 0.5f, -1.0f );
	EventDispatcher::Instance().addEvent( l_transEvent );

	LightEvent* l_lightevent = new LightEvent( l_pointLight );
	l_lightevent->positionToAdd.set( 2.0f, 1.0f, -1.0f );
	
	l_lightevent->ambientToAdd.set( 0.1f,0.1f,0.1f );
	l_lightevent->newDirection.set( -0.0f, -1.0f, -0.0f );
	l_lightevent->diffuse.set( 0.5f, 0.5f, 0.5f );
	l_lightevent->specular.set( 0.5f, 0.5f, 0.5f );
	EventDispatcher::Instance().addEvent( l_lightevent );


	/*long grassID = l_core.createNewEntity( "grass" );
	l_compData.clear();
	l_compData.push_back( "render" );
	l_compData.push_back( "gras.xml" );
	l_compData.push_back( "basic" );
	l_core.addComponentToEntity( grassID, "basic", l_compData );
	l_compData.clear();
	l_core.addComponentToEntity( grassID, "basic", "translation" );

	TranslationsEvent* l_transEventGrass = new TranslationsEvent( grassID );
	l_transEventGrass->m_positionsOffset.set( 0.0f,0.0f,0.0f );
	l_transEventGrass->m_rotationOffset.setX( -90.0f );
	EventDispatcher::Instance().addEvent( l_transEventGrass );*/

	// Directional light
	long a_dirLigt = l_core.createNewEntity( "dirlight" );
	l_compData.clear();
	l_compData.push_back( "light" );
	l_compData.push_back( "lightsource" );
	l_compData.push_back( "0" );
	l_core.addComponentToEntity( a_dirLigt, "basic", l_compData );
	l_compData.clear();

	LightEvent* l_lightevent2 = new LightEvent( a_dirLigt );
	l_lightevent2->positionToAdd.set( 2.0f, 5.0f, -3.0f );
	l_lightevent2->newDirection.set( -0.2f, -1.0f, -0.3f );
	l_lightevent2->ambientToAdd.set( 0.1f, 0.1f, 0.1f );
	l_lightevent2->diffuse.set( 0.75f, 0.75f, 0.75f );
	l_lightevent2->specular.set( 0.75f, 0.75f, 0.75f );
	EventDispatcher::Instance().addEvent( l_lightevent2 );

	//skybox
	l_compData.clear();
	l_compData.push_back( "cubemap" );
	l_compData.push_back( "skybox" );
	l_compData.push_back( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\textures\\cubemap\\left.png" );
	l_compData.push_back( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\textures\\cubemap\\right.png" );
	l_compData.push_back( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\textures\\cubemap\\top.png" );
	l_compData.push_back( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\textures\\cubemap\\bottom.png" );
	l_compData.push_back( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\textures\\cubemap\\back.png" );
	l_compData.push_back( "C:\\Users\\episch\\Documents\\OpenGLProject\\BasicOpenGLModules\\BasicOpenGLModules\\textures\\cubemap\\front.png" );
	long skyboxID = l_core.createNewEntity( "skybox" );
	l_core.addComponentToEntity( skyboxID, "basic", l_compData );
	l_core.addComponentToEntity( skyboxID, "basic", "translation" );


	InputSystem* l_inputSystem = new InputSystem( &l_mainWindow, &l_core.getEntityCollection() );
	BasicKeyInput* l_keyInput = new BasicKeyInput();
	l_inputSystem->addKeyEvent( l_keyInput );

	TranslationSystem* l_translationSystem = new TranslationSystem(&l_core.getEntityCollection() );

	RenderSystem* l_renderSystem = new RenderSystem( &l_core.getEntityCollection(), &l_shaderManager );

	CameraSystem* l_cameraSystem = new CameraSystem( &l_core.getEntityCollection() );

	Lightsystem* l_lightSystem = new Lightsystem( &l_core.getEntityCollection(), &l_shaderManager, l_core.getEntityCollection().getEntityByID(l_camID) );
	

	l_core.addSystem( l_inputSystem ); // first handle input
	l_core.addSystem( l_translationSystem ); // then do the translation
	l_core.addSystem( l_lightSystem ); // lightning befor rendering
	l_core.addSystem( l_cameraSystem ); // Update camera
	l_core.addSystem( l_renderSystem ); // render everything

	l_core.startMainLoop(); // Start the main loop


	
	return 0;
}