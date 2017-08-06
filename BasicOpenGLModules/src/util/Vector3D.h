#pragma once
#include <glm\glm.hpp>
#include <rapidXml\rapidxml.hpp>


namespace util
{

	enum EnVectorIndex {
		e_x,
		e_y,
		e_z
	};

	/**
	 * Class which represents a 3D Vector.
	 */

	template <typename T>
	class Vector3D
	{
	public:

		/**
		 * Constructor
		 */
		Vector3D()
		{
			m_x = 0;
			m_y = 0;
			m_z = 0;
		}

		/**
		 * Constructor
		 * @author sascha blank
		 * @param p_x, the x axis
		 * @param p_y, the y axis
		 * @param p_z, the z axis
		 */
		Vector3D(T p_x, T p_y, T p_z)
		{
			m_x = p_x;
			m_y = p_y;
			m_z = p_z;
		}

		T getX() const { return m_x; }
		T getY() const { return m_y; }
		T getZ() const { return m_z; }


		void setX(float p_x) { m_x = p_x; }
		void setY(float p_y) { m_y = p_y; }
		void setZ(float p_z) { m_z = p_z; }
		void set(float p_x, float p_y, float p_z)
		{
			m_x = p_x;
			m_y = p_y;
			m_z = p_z;
		}

		void set(EnVectorIndex t_index, float t_value)
		{
			switch (t_index)
			{
			case e_x:
				m_x = t_value;
				break;
			case e_y:
				m_y = t_value;
				break;
			case e_z:
				m_z = t_value;
				break;
			}
		}
		Vector3D(const Vector3D& t_other)
		{
			if (this != &t_other)
			{
				*this = t_other;
			}
		}

		Vector3D& operator=(const Vector3D& t_other)
		{
			if (this != &t_other)
			{
				m_x = t_other.m_x;
				m_y = t_other.m_y;
				m_z = t_other.m_z;
			}
			return *this;
		}

		T* getAsArray(void)
		{
			T r_array = new T[3];
			r_array[0] = m_x;
			r_array[1] = m_y;
			r_array[2] = m_z;
			return r_array;
		}

		Vector3D operator+(const Vector3D<T>& t_rhv)
		{
			Vector3D<T>r_result;
			r_result.m_x = m_x + t_rhv.m_x;
			r_result.m_y = m_y + t_rhv.m_y;
			r_result.m_z = m_z + t_rhv.m_z;
			return r_result;
		}

		Vector3D operator-(const Vector3D<T>& t_rhv)
		{
			Vector3D<T>r_result;
			r_result.m_x = m_x - t_rhv.m_x;
			r_result.m_y = m_y - t_rhv.m_y;
			r_result.m_z = m_z - t_rhv.m_z;
			return r_result;
		}

		glm::vec3 convertToGlmVec3()
		{
			glm::vec3 r_vec( m_x, m_y, m_z );
			return r_vec;
		}



	private:
		T m_x;
		T m_y;
		T m_z;
	};

	typedef Vector3D<float> VectorF;
	typedef Vector3D<int> VectorI;
	typedef Vector3D<double> VectorD;

}