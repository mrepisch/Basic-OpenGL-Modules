#pragma once
#include "IComponentFactory.h"
#include "ShaderManager.h"

namespace core
{
	class BasicComponentFactory : public IComponentFactory
	{
	public:

		BasicComponentFactory( ShaderManager* p_shaderManager );

		component::Component* generateComponentFromVector( const std::vector<std::string>& p_data );

		component::Component* generateComponentFromMap( const std::map<std::string, std::string>& p_data );

		component::Component* generateComponentFromString( const std::string& t_data );

	private:
		ShaderManager* m_shaderManager;
	};
}