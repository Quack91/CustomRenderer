// Renderer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "tgaimage.h"

const int width = 200;
const int height = 200;

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

void draw_line(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color);

int main()
{
	TGAImage image(width, height, TGAImage::RGB);

	draw_line(10, 10, 100, 20, image, white);
	// Image is flipped vertically, to show it from bottom-left corner.
	image.flip_vertically();

	image.write_tga_file("output.tga");
}

void draw_line(int x1, int y1, int x2, int y2, TGAImage& image, const TGAColor& color)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	float m = deltaY / static_cast<float>(deltaX);

	int b = y1 - m * x1;

	int y = y1;
	for (int x = x1; x <= x2; x++)
	{
		y = m * x + b;
		image.set(x, y, color);
	}
}

