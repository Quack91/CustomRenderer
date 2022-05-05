// Renderer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "tgaimage.h"
#include "geometry.h"
#include "mesh.h"

const int width = 200;
const int height = 200;

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

void draw_line_naive(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color);
void draw_line_dda(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color);
void draw_line_bresenham(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color);

int main()
{
	mesh mesh("obj/african_head.obj");
}

void draw_line_naive(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color)
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

void draw_line_dda(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color)
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

void draw_line_bresenham(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color)
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