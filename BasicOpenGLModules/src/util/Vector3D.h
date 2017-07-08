#pragma once

enum VectorIndex {
	e_x = 0,
	e_y = 1,
	e_z = 2;
};

template <typename T>
class Vector3D
{

public:

	Vector3D()
	{
		m_x = 0;
		m_y = 0;
		m_z = 0;
	}

	Vector3D(T p_x, T p_y, T p_z)
	{
		m_x = p_x;
		m_y = p_y;
		m_z = p_z;
	}
	
	T getX() const { return m_x; }
	T getY() const { return m_y; }
	T getZ() const { return m_z; }

	T operator[](VectorIndex p_index)
	{
		T r_value = 0;
		if (p_index = 0)
		{
			r_value = m_x;
		}
		else if (p_index == 1)
		{
			r_value = m_y;
		}
		else if (p_index == 2)
		{
			r_value = m_z;
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
	}

private:
	T m_x;
	T m_y;
	T m_z;
};

