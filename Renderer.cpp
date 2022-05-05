// Renderer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "geometry.h"
#include "mesh_renderer.h"

const int width = 800;
const int height = 800;

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

int main()
{
	TGAImage image(width, height, TGAImage::RGB);
	mesh mesh("obj/african_head.obj");
	mesh_renderer renderer;

	renderer.draw(mesh, image, white, Vector2Int(width, height));

	image.flip_vertically();
	image.write_tga_file("output.tga");
}