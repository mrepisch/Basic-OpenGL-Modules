#include "RenderComponent.h"


using namespace render;
using namespace component;

RenderComponent::RenderComponent( render::Mesh* p_mesh ) : Component(e_renderComponent)
{
	m_mesh = p_mesh;
}


RenderComponent::~RenderComponent( void )
{
	delete m_mesh;
}