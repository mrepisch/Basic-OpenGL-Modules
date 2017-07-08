#pragma once

enum EnVectorIndex {
	e_x,
	e_y,
	e_z
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
	}

private:
	T m_x;
	T m_y;
	T m_z;
};

