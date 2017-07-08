#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> StringVec;

class Util
{
public:
	static StringVec SplitWithWiteSpace( std::string& t_split );
};


