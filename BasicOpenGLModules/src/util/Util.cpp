

#include "Util.h"
#include <iostream>
#include <sstream>


StringVec Util::SplitWithWiteSpace( std::string& t_toSplit)
{
	
	StringVec r_result;

	std::istringstream iss(t_toSplit);
	for (std::string s; iss >> s; )
		r_result.push_back(s);
	return r_result;
}