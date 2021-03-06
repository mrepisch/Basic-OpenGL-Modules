
// Internal includes
#include "BasicKeyInput.h"
#include "game\CameraEvent.h"
#include "component\EventDispatcher.h"
#include "util\Vector3D.h"

using namespace game;
using namespace component;
using namespace util;

BasicKeyInput::BasicKeyInput( void )
{
	addKey( SDLK_w );
	addKey( SDLK_e );
	addKey( SDLK_s );
	addKey( SDLK_q );
	addKey( SDLK_a );
	addKey( SDLK_d );	
	addKey( SDLK_y );
	addKey( SDLK_x );
}


BasicKeyInput::~BasicKeyInput( void )
{

}


void BasicKeyInput::processEvent( const SDL_Event& t_event )
{
	switch (t_event.key.keysym.sym)
	{
	case SDLK_w:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->direction = CameraEvent::e_forward;
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}
	case SDLK_e:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->setRotation( VectorF( 3.0f, 0.0f, 0.0f ) );
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}
	case SDLK_s:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->direction = CameraEvent::e_backward;
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}
	case SDLK_q:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->setRotation( VectorF( -3.0f, 0.0f, 0.0f ) );
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}
	case SDLK_a:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->direction = CameraEvent::e_left;
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}
	case SDLK_d:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->direction = CameraEvent::e_right;
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}
	case SDLK_y:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->setRotation( VectorF( 0.0f, 3.0f, 0.0f ) );
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}
	case SDLK_x:
	{
		CameraEvent* l_cameraEvent = new CameraEvent();
		l_cameraEvent->setRotation( VectorF( 0.0f, -3.0f, 0.0f ) );
		EventDispatcher::Instance().addEvent( l_cameraEvent );
		break;
	}

	default:
		break;
	}
}