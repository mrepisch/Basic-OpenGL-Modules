#pragma once
#include <glew\GL\glew.h>
#include <string>
#include <map>
#include <glm\glm.hpp>
namespace core
{
	class ShaderManager
	{
	public:
		enum EnShaderType
		{
			e_vertex = 0,
			e_fragment
		};

		ShaderManager();
		virtual ~ShaderManager();

		void createShaderProgram( const std::string& t_programName );

		GLuint getShaderProgramID( const std::string& p_name );

		void useProgram( const std::string& p_name );

		void useProgram( GLuint p_programID );

		void addShader( const std::string& t_shaderName, EnShaderType t_type, const std::string& t_shaderFile, const std::string& t_programName );
		void compile( void );

		void setVector( glm::vec3 p_vec, const std::string& p_uniformName, const std::string& p_shaderProgramName);

		void setVector( glm::vec3 p_vec, const std::string& p_uniformName, GLuint p_shaderProgrammID );

		void setMatrix( glm::mat4 p_matrix, const std::string& p_uniformName, const std::string& p_shaderProgramName );

		void setMatrix( glm::mat4 p_matrix, const std::string& p_uniformName, GLuint p_shaderProgrammID );

		void setFloat( float p_value, const std::string& p_uniformName, GLuint p_shaderProgrammID );

		void setFloat( float p_value, const std::string& p_uniformName, const std::string& p_shaderProgrammID );

		void setInt( int p_value, const std::string& p_uniformName, GLuint p_shaderProgramID );

		void setInt( int p_value, const std::string& p_uniformName, const std::string& p_shaderProgramName );

	private:
		std::map<std::string, GLuint>m_shaderPrograms;

	
	};
}