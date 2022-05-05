#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "mesh.h"

mesh::mesh(const char* filename) : m_vertices(), m_textures(), m_normals(), m_faces()
{
	/** Opening file containing model. */
	std::ifstream in;
	in.open(filename, std::ifstream::in);

	/** Failed loading file. */
	if (in.fail())
		return;

	std::string line;
	char trash;
	while (getline(in, line))
	{
		std::istringstream iss(line.c_str());
		if(line.compare(0, 2, "v ") == 0) // geometric vertices (x, y, z [,w])
		{
			iss >> trash;

			Vector3 vertice;
			for (int i = 0; i < 3; i++)
			{
				iss >> vertice.raw[i];
			}

			m_vertices.push_back(vertice);
		}
		else if (line.compare(0, 2, "vt") == 0) //texture coordinates (u [,v ,w])
		{
			iss >> trash;

			Vector2 texture_coordinate;
			for (int i = 0; i < 2; i++) 
			{
				iss >> texture_coordinate.raw[i];
			}

			m_textures.push_back(texture_coordinate);
		}
		else if (line.compare(0, 2, "vn") == 0) //vertex_normals
		{
			iss >> trash;

			Vector3 vertex_normal;
			for (int i = 0; i < 3; i++)
			{
				iss >> vertex_normal.raw[i];
			}

			m_normals.push_back(vertex_normal);
		}
		else if (line.compare(0, 2, "f ") == 0) //faces
		{
			face face;
			int vertex_index, texture_index, normal_index;

			iss >> trash;

			/* f line in wavefront obj contains: vertex_index/texture_index/normal_index. */
			while (iss >> vertex_index >> trash >> texture_index >> trash >> normal_index)
			{
				/* In wavefront obj all indices start at 1, not zero, so we subtract to avoid index out of array. */
				vertex_index--;
				texture_index--;
				normal_index--;

				face.Vertices.push_back(vertex_index);
				face.Textures.push_back(texture_index);
				face.Normals.push_back(normal_index);
			}

			m_faces.push_back(face);
		}
	}
}

Vector3 mesh::GetVertex(int index) const
{
	return m_vertices[index];
}

Vector2 mesh::GetTexture(int index) const
{
	return m_textures[index];
}

Vector3 mesh::GetNormal(int index) const
{
	return m_normals[index];
}

face mesh::GetFace(int index) const
{
	return m_faces[index];
}

int mesh::GetVerticesCount() const
{
	return static_cast<int>(m_vertices.size());
}

int mesh::GetTexturesCount() const
{
	return static_cast<int>(m_textures.size());
}

int mesh::GetNormalsCount() const
{
	return static_cast<int>(m_normals.size());
}

int mesh::GetFaceCount() const
{
	return static_cast<int>(m_faces.size());
}
