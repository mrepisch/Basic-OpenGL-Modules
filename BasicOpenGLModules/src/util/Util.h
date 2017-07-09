#pragma once

#include <vector>
#include <string>


namespace util
{
	typedef std::vector<std::string> StringVec;

	class Util
	{
	public:
		static StringVec SplitWithWiteSpace(std::string& t_split);
	};
}


