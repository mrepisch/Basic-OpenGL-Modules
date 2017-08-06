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
	l_core.addComponentFactory( "basic", &l_factory );

	l_core.loadSzene( "C:\\Users\\episch\\Documents\\testSzene.xml", "basic" );

	InputSystem* l_inputSystem = new InputSystem( &l_mainWindow, &l_core.getEntityCollection() );
	BasicKeyInput* l_keyInput = new BasicKeyInput();
	l_inputSystem->addKeyEvent( l_keyInput );

	TranslationSystem* l_translationSystem = new TranslationSystem(&l_core.getEntityCollection() );

	RenderSystem* l_renderSystem = new RenderSystem( &l_core.getEntityCollection(), &l_shaderManager );

	CameraSystem* l_cameraSystem = new CameraSystem( &l_core.getEntityCollection() );

	//Lightsystem* l_lightSystem = new Lightsystem( &l_core.getEntityCollection(), &l_shaderManager, l_core.getEntityCollection().getEntityByID(l_camID) );
	

	l_core.addSystem( l_inputSystem ); // first handle input
	l_core.addSystem( l_translationSystem ); // then do the translation
	//l_core.addSystem( l_lightSystem ); // lightning befor rendering
	l_core.addSystem( l_cameraSystem ); // Update camera
	l_core.addSystem( l_renderSystem ); // render everything

	//l_core.saveSzene( "C:\\Users\\episch\\Documents\\testSzene.xml" );

	l_core.startMainLoop(); // Start the main loop


	
	return 0;
}