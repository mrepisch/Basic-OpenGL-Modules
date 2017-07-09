#pragma once

// External includes
#include<glew\GL\glew.h>

// Internal includes
#include "IMeshRender.h"
#include "Mesh.h"

/**
* Implementation of the IMeshRenderer interface.
* It uses glVertex etc( the oldscool stuff) in order to render Meshes
*/
class GLClassicMeshRender : public IMeshRender
{
public:

	/**
	 * Constructor. 
	 * @author sascha Blank
	 * @param p_mesh, pointer on the mesh to draw
	 */
	GLClassicMeshRender( Mesh* p_mesh );

	// empty Function
	void init();

	/**
	 * Render function which is called in the main loop
	 */
	void render();

private:
	
	// The mesh to render 
	Mesh* m_mesh;
};