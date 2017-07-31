#pragma once


#include "../render/Mesh.h"



namespace util
{
	class ModelLoader
	{
	public:
		ModelLoader();
		virtual ~ModelLoader();
		render::Mesh* loadOBJFile( const char* t_file );

	private:
		
		

	};
}