#pragma once

// External includes
#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include <map>

namespace core
{
	/**
	 * This class handles the all the Shaders. 
	 * In order to use this class the fallowing steps are requiert:
	 * 1) Create a new Shader Programm
	 * 2) Add a vertex and a fragment shader
	 * 3) Use the compile function
	 * 4) Call the programm whith the given ID or Shaderprogramm name
	 */
	class ShaderManager
	{
	public:
		enum EnShaderType
		{
			e_vertex = 0,
			e_fragment
		};

		/**
		 * Constructor
		 * @author sascha blank
		 */
		ShaderManager();

		/**
		 * Virtual Destructor
		 */
		virtual ~ShaderManager();

		/**
		 * Function to create a shader programm which is saved under the given name
		 * @author sascha blank
		 * @param const std::string& the shaderprogramm name
		 */
		void createShaderProgram( const std::string& p_programName );

		/**
		 * Function to return the Shaderprogramm id with the given name
		 * @author sascha blank
		 * @param const std::string& the shaders programm name
		 */
		GLuint getShaderProgramID( const std::string& p_name );

		/**
		 * Uses a shader programm with the given name
		 * @author sascha blank
		 * @param const std::string& shaders programm name
		 */
		void useProgram( const std::string& p_name );

		/**
		 * Use a shader programm with the given id
		 * @author sascha blank
		 * @param GLuint the shaders programm id
		 */
		void useProgram( GLuint p_programID );

		/**
		 * Function to add a shader to the given programm
		 * @author sascha blank
		 * @param const std::string, the name of the shader
		 * @param EnShaderType the enum type definition
		 * @param const std::string& the file path of the shaders code
		 * @param const std::string& the shader programm name to add the shader to.
		 */
		void addShader( const std::string& t_shaderName, EnShaderType t_type, const std::string& t_shaderFile, const std::string& t_programName );

		/**
		 * Function to compile all shader programms
		 * @author sascha blank
		 */
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