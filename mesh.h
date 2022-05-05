#pragma once

#include <vector>
#include "geometry.h"

struct face;

class mesh
{
public:
	mesh(const char* filename);

	Vector3 GetVertex(int index) const;
	Vector2 GetTexture(int index) const;
	Vector3 GetNormal(int index) const;
	face GetFace(int index) const;

	int GetVerticesCount() const;
	int GetTexturesCount() const;
	int GetNormalsCount() const;
	int GetFaceCount() const;
private:
	std::vector<Vector3> m_vertices;
	std::vector<Vector2> m_textures;
	std::vector<Vector3> m_normals;
	std::vector<face> m_faces;
};

struct face
{
	std::vector<int> Vertices;
	std::vector<int> Normals;
	std::vector<int> Textures;
};

