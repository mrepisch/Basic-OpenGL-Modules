#pragma once

#include <vector>
#include <string>
#include <map>

#include "../component/Component.h"

namespace core
{
	/**
	 * This interface is used in the BasicOpenGLCore for generating components for Entitys.
	 * 
	 */
	class IComponentFactory
	{
	public:
		virtual component::Component* generateComponentFromVector( const std::vector<std::string>& p_data ) = 0;

		virtual component::Component* generateComponentFromMap(const std::map<std::string,std::string>& p_data ) = 0;

		virtual component::Component* generateComponentFromString( const std::string& t_data ) = 0;

	};
}
