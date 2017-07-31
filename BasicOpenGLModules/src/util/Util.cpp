
// External includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <direct.h>

// Internal includes
#include "Util.h"

using namespace std;
using namespace util;

StringVec Util::SplitWithWiteSpace( std::string& t_toSplit)
{
	
	StringVec r_result;

	std::istringstream iss(t_toSplit);
	for (std::string s; iss >> s; )
		r_result.push_back(s);
	return r_result;
} 



std::string Util::readFile( const char* p_filename )
{
	string r_data;
	std::ifstream file( p_filename );
	std::string str;
	while (std::getline( file, str ))
	{
		r_data += str + "\n";
	}
	file.close();
	return r_data;
}


std::string Util::getBasePath( void )
{
	char *path = NULL;
	path = getcwd( NULL, 0 ); // or _getcwd
	std::string workingDir = path;
	return workingDir;
}