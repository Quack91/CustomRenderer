#pragma once
#include "mesh.h"
#include "tgaimage.h"

class mesh_renderer
{
public:
	void draw(mesh& mesh, TGAImage& image, const TGAColor& color, const Vector2Int& screen_size) const;

protected:
	void draw_triangle(Vector2Int* points, TGAImage& image, const TGAColor& color) const;

	void draw_line_naive(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color) const;
	void draw_line_dda(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color) const;
	void draw_line_bresenham(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color) const;
};

