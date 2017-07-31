
// External includes
#include <OBJ_Loader.h>
#include <iostream>
#include <list>
// Internal includes
#include "ModelLoad.h"


using namespace util;
using namespace render;


ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

Mesh* ModelLoader::loadOBJFile( const char* t_file )
{
	Mesh* r_mesh = new Mesh();
	objl::Loader l_loader;
	if (l_loader.LoadFile( t_file ))
	{
		for (int i = 0; i < l_loader.LoadedVertices.size(); ++i)
		{
			Vertex* l_vertex = new Vertex();
			l_vertex->position.set( l_loader.LoadedVertices[ i ].Position.X,
				l_loader.LoadedVertices[ i ].Position.Y,
				l_loader.LoadedVertices[ i ].Position.Z );

			l_vertex->textureCords.set( l_loader.LoadedVertices[ i ].TextureCoordinate.X,
				l_loader.LoadedVertices[ i ].TextureCoordinate.Y,
				0.0f );
			l_vertex->id = i;
			r_mesh->addVertex( l_vertex );

		}
		for (int i = 0; i < l_loader.LoadedIndices.size(); i += 3)
		{
			Face* l_face = new Face();
			l_face->vertcies[ 0 ] = l_loader.LoadedIndices[ i ];
			l_face->vertcies[ 2 ] = l_loader.LoadedIndices[ i + 1];
			l_face->vertcies[ 2 ] = l_loader.LoadedIndices[ i + 2];
			r_mesh->addFace( l_face );
		}
	}
	return r_mesh;
}
