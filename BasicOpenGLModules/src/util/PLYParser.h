#pragma once

#include <string>
#include "../render/Mesh.h"

namespace util
{
	class PLYParser
	{
	public:
		render::Mesh* readMeshFromFile(const std::string& p_filename);


	};
}