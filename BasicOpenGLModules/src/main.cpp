#include <iostream>
#include <glew\GL\glew.h>
#include "Display.h"
#include "util\Vector3D.h"
#include "render\RenderSystem.h"
#include "render\RenderComponent.h"
#include "component\TranslationComponent.h"
#include "util\PLYParser.h"

using namespace render;
using namespace component;
using namespace util;

int main(int argc, char **argv)
{

	

	Display l_mainWindow(800, 600, "OpenGL Window");
	l_mainWindow.setFPS( 30 );
	

	RenderSystem* l_renderSystem = new RenderSystem();
	l_mainWindow.addSystem( l_renderSystem, component::EnEventType::e_renderEvent );

	PLYParser a_parser;
	Entity* l_entity = new Entity("testobject");
	
	Mesh* a_mesh = a_parser.readMeshFromFile( "C:\\Users\\episch\\Documents\\test.ply" );
	a_mesh->setTexture( new Texture( "C:\\Users\\episch\\Documents\\OpenGLProject\\test.bmp" ) );
	RenderComponent* a_renderComponent = new RenderComponent(a_mesh);
	TranslationComponent* a_translation = new TranslationComponent();
	a_translation->m_position.set( 0.0f, 0.0f, -4.0f );
	a_translation->m_rotation.set( 45.0f, 45.0f, 45.0f );
	l_entity->addComponent( a_translation );
	l_entity->addComponent( a_renderComponent );
	l_mainWindow.addEntity( l_entity );

	l_mainWindow.update();
	return 0;
}