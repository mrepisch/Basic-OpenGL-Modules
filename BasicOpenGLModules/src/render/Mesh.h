#pragma once

#include "util\Vector3D.h"
#include <list>

class Vertex
{
public:
	VectorF position;
	VectorF color;

	Vertex()
	{
		position.set(0.0f, 0.0f, 0.0f);
		color.set(0.0f, 0.0f, 0.0f);
	}

	Vertex (const Vertex& t_other)
	{
		if (this != &t_other)
		{
			*this = t_other;
		}
	}

	Vertex& operator=(const Vertex& t_other)
	{
		if (this != &t_other)
		{
			position = t_other.position;
			color = t_other.color;
		}
		return *this;
	}
};

class Face
{
public:
	Vertex vertcies[3];
	
	Face()
	{
		// empty body
	}

	Face(const Face& t_other)
	{
		if (this != &t_other)
		{
			*this = t_other;
		}
	}

	Face& operator=(const Face& t_other) 
	{
		if (this != &t_other)
		{
			vertcies[0] = t_other.vertcies[0];
			vertcies[1] = t_other.vertcies[1];
			vertcies[2] = t_other.vertcies[2];
		}
	}
};


class Mesh
{
public:
	Mesh( );
	virtual ~Mesh();

	void addFace(Face* p_face);
	const std::list<Face*>& getFaces(void) const;
	
	void initMesh();

	void render();

private:

	std::list<Face*>m_faces;



	

};

