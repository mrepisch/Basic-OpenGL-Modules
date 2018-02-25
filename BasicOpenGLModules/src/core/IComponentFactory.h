#pragma once

// External includes
#include <vector>
#include <string>
#include <map>
#include <rapidXml\rapidxml.hpp>

// Internal includes
#include "../component/Component.h"

namespace core
{
	/**
	 * This interface is used in the BasicOpenGLCore for generating components for Entitys.
	 * For using the OpenGL Basic Modules core you have to implement the IComponentFactory for your own Components.
	 * The BasicComponentFactory is one Basic implementation of this interfaces in order to generate the allready used components.
	 * @author sascha blank
	 */
	class IComponentFactory
	{
	public:

		/**
		 * Function to generate Components with the given std::vector. The first entry in the vector ( p_data[0] ) is usualy the component names
		 * and the other entrys are for the data which the component shoud use.
		 * @author sascha blank
		 * @param const std::vector<std::string>& the data for the component.
		 */
		virtual component::Component* generateComponentFromVector( const std::vector<std::string>& p_data ) = 0;

		/**
		 * Same as above but insteat of using an std::vector its using an std::map
		 * @author sascha blank
		 */
		virtual component::Component* generateComponentFromMap(const std::map<std::string,std::string>& p_data ) = 0;

		/**
		 * Same as above but insteat of using a std::vector the function takes an std::string
		 * @author sascha blank
		 */
		virtual component::Component* generateComponentFromString( const std::string& t_data ) = 0;

		/**
		 * Function to load components from xml nodes
		 * @author sascha blank
		 * @param rapidxml::xml_node<>* the node to read from
		 */
		virtual component::Component* generateComponentFromXmlNode( rapidxml::xml_node<>* p_node ) = 0;
	};
}
