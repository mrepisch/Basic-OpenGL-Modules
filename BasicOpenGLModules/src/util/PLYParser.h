#pragma once

#include <string>
#include "../render/Mesh.h"


class PLYParser
{
public:
	Mesh* readMeshFromFile(const std::string& p_filename);


};