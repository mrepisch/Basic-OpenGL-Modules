#pragma once

// External includes
#include <list>

// Internal includes
#include "util\Vector3D.h"
#include "Texture.h"

/**
 * This class represents one single Vertex
 * It holds a position, a color and The texture cordinates
 * @author sascha blank
 */

class Vertex
{
public:
	VectorF position;
	VectorF color;
	VectorF textureCords;

	Vertex()
	{
		position.set(0.0f, 0.0f, 0.0f);
		color.set(0.0f, 0.0f, 0.0f);
		textureCords.set(0.0f,0.0f,0.0f);
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
			textureCords = t_other.textureCords;
		}
		return *this;
	}
};


/**
 * This clas represents a face which holds 3 Vertecis
 * @author sascha blank
 */
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


/**
 * This class represents the Mesh to render with all the faces needed.
 * Just create a new Mesh object and add faces to it.
 * @author sascha blank
 */
class Mesh
{
public:
	
	/**
	 * Default constructor
	 * @author Sascha Blank
	 */
	Mesh( void );

	/**
	 * Constructor with a texture.
	 * @author sascha blank
	 * @param p_texture, the texture the mash is using
	 */
	Mesh(Texture* p_texture);

	/**
	 * Constructor with the texture file path
	 * @author sascha blank
	 * @param p_textureFilePath, the path to the texture.
	 */
	Mesh(const char* p_textureFilePath);
	
	/**
	 * Virtual destructor
	 * @author sascha blank
	 */
	virtual ~Mesh();

	/**
	 * Add a new Face to the mesh.
	 * @author sascha Blank
	 * @param p_face, pointer to the face which is added to the mesh
	 */
	void addFace(Face* p_face);

	/**
	 * Function to return all faces of the mesh
	 * @author sascha Blank
	 * @return const std::list<Face*>&, list with all faces of the mesh
	 */
	const std::list<Face*>& getFaces(void) const;

	/**
	 * Getter on the Texture pointer.
	 * @author sascha blank
	 * @return const Texture* 
	 */
	GLuint getTextureID(void);

	void setTexture(Texture* p_texture);

	
private:

	//List with all faces of the mesh
	std::list<Face*>m_faces;

	// Texture to use
	Texture* m_texture;

};

