#include <sstream>
#include <string>
#include <fstream>
#include "PLYParser.h"
#include "Util.h"

using namespace util;
using namespace render;

Mesh* PLYParser::readMeshFromFile(const std::string& p_filename)
{
	std::ifstream l_infile(p_filename);
	std::string l_line;
	int l_vertexCount = 0;
	int l_facesCount = 0;
	
	bool l_readVertecis = false;
	bool l_readFaces = false;
	int l_vertecisReadCounter = 0;
	int l_faceReadCounter = 0;
	Mesh* r_mesh = new Mesh();

	Vertex* l_vertecis = nullptr;
	while (std::getline(l_infile, l_line))
	{
		if (l_line.find("element vertex ") != -1)
		{
			StringVec l_split = Util::SplitWithWiteSpace(l_line);
			l_vertexCount = std::atoi(l_split[l_split.size() - 1].c_str());
		}
		if(l_line.find("element face ") != -1)
		{
			StringVec l_split = Util::SplitWithWiteSpace(l_line);
			l_facesCount = std::atoi(l_split[l_split.size() - 1].c_str());
		}
		 if (l_line.compare("end_header") == 0)
		{
			l_readVertecis = true;
			l_vertecis = new Vertex[l_vertexCount];
		}
		else if (l_readVertecis && l_vertecisReadCounter < l_vertexCount)
		{
			StringVec l_split = Util::SplitWithWiteSpace(l_line);
			l_vertecis[l_vertecisReadCounter] = *(new Vertex());
			l_vertecis[l_vertecisReadCounter].position.set(std::stof(l_split[0].c_str()), std::stof(l_split[1].c_str()), std::stof(l_split[2].c_str()));
			if (l_split.size() >= 7)
			{
				l_vertecis[l_vertecisReadCounter].textureCords.set(std::stof(l_split[6].c_str()), std::stof(l_split[7].c_str()), 0.0f);
			}
			++l_vertecisReadCounter;
		}
		else if (l_readVertecis && l_vertecisReadCounter >= l_vertexCount)
		{
			l_readVertecis = false;
			l_readFaces = true;
		}
	    if (l_readFaces && l_faceReadCounter < l_facesCount)
		{
			if (l_vertecis != nullptr)
			{
				Face* l_face = new Face();
				StringVec l_split = Util::SplitWithWiteSpace(l_line);
				l_face->vertcies[0] = l_vertecis[std::atoi(l_split[1].c_str())];
				l_face->vertcies[1] = l_vertecis[std::atoi(l_split[2].c_str())];
				l_face->vertcies[2] = l_vertecis[std::atoi(l_split[3].c_str())];
				r_mesh->addFace(l_face);
				++l_faceReadCounter;
			}
		}
	}
	return r_mesh;
}