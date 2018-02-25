
#pragma once

#include <map>
#include <string>
#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>

namespace core
{

	class Shader
	{
	public:
		enum EnShaderPosition
		{
			e_beforRender = 0,
			e_midRender,
			e_afterRender
		};

		Shader( const char* p_fileOrCode, bool p_isFile );
		
		void setMatrixData( const std::string p_name, glm::mat4x4 p_matrix );

		void setVectorData( const std::string p_name, glm::vec3 p_vec );

		virtual void update() = 0;

	private:

		void compile(  );

		std::map<std::string, glm::mat4x4>m_matrixes;
		std::map<std::string, glm::vec3>m_vectors;

	};
}