
// External includes
#include <iostream>
#include <sstream>

// Internal includes
#include "Util.h"

using namespace util;

StringVec Util::SplitWithWiteSpace( std::string& t_toSplit)
{
	
	StringVec r_result;

	std::istringstream iss(t_toSplit);
	for (std::string s; iss >> s; )
		r_result.push_back(s);
	return r_result;
}