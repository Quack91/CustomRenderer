#include "mesh_renderer.h"
#include "tgaimage.h"

void mesh_renderer::draw(mesh& mesh, TGAImage& image,const TGAColor& color, const Vector2Int& screen_size) const
{
	int faceCount = mesh.GetFaceCount();

	for (int i = 0; i < faceCount; i++)
	{
		face face = mesh.GetFace(i);

		Vector2Int screen_coordinates[3];

		for (int j = 0; j < 3; j++)
		{
			Vector3 vertex = mesh.GetVertex(face.Vertices[j]);
			int x = (vertex.x + 1.f) * screen_size.x * 0.5f;
			int y = (vertex.y + 1.f) * screen_size.y * 0.5f;
			screen_coordinates[j] = Vector2Int(x, y);
		}

		draw_triangle(screen_coordinates, image, color);
	}
}

void mesh_renderer::draw_triangle(Vector2Int* points, TGAImage& image, const TGAColor& color) const
{
	for (int i = 0; i < 3; i++)
	{
		Vector2Int screenPoint = points[i];
		Vector2Int nextScreenPoint = points[(i + 1) % 3];
		draw_line_bresenham(screenPoint.x, screenPoint.y, nextScreenPoint.x, nextScreenPoint.y, image, color);
	}
}

void mesh_renderer::draw_line_naive(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color) const
{
	if (x2 < x1)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	bool inversed = std::abs(x2 - x1) < std::abs(y2 - y1);
	if (inversed)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	float m = deltaY / static_cast<float>(deltaX);

	int b = y1 - m * x1;

	int y = y1;
	for (int x = x1; x <= x2; x++)
	{
		y = m * x + b;
		if (inversed)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
	}
}

void mesh_renderer::draw_line_dda(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color) const
{

	float x, y, dx, dy, step;

	x = x1;
	y = y1;

	dx = x2 - x1;
	dy = y2 - y1;

	if (std::abs(dx) >= std::abs(dy))
		step = std::abs(dx);
	else
		step = std::abs(dy);

	if (!step)
		return;

	dx = dx / step;
	dy = dy / step;

	for (int i = 1; i <= step; i++)
	{
		image.set(x, y, color);

		x += dx;
		y += dy;
	}
}

void mesh_renderer::draw_line_bresenham(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color) const
{

	//checking for line steepness
	bool isSteep = std::abs(x2 - x1) < std::abs(y2 - y1);
	if (isSteep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	// making sure that we are going from left to right
	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	//calculating deltas
	int dx = x2 - x1;
	int dy = y2 - y1;
	int sign = 1;

	//making sure that we use a proper sign when add to y value
	if (dy < 0)
	{
		dy = -dy;
		sign = -1;
	}

	//caching added values of deltas that are used later
	int dy2 = dy + dy;
	int dx2 = dx + dx;

	//calculating decision parameter
	int dp = dy2 - dx;

	//caching y value
	int y = y1;

	//checking every point
	for (int x = x1; x <= x2; x++)
	{
		if (isSteep)
			image.set(y, x, color);
		else
			image.set(x, y, color);

		//check if case 2 is satisfied
		if (dp > 0)
		{
			dp -= dx2;
			y += sign;
		}

		dp += dy2;
	}
}