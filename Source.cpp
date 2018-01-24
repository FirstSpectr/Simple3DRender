#include <iostream>
#include "windows.h"
#include <ctime>
#include <cmath>
#include "Model.h"
#include "MyMath.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>


const int width = 400, height = 400, depth = 255;

void line(int x0, int y0, int x1, int y1, sf::Image &image, sf::Color color) {
	bool steep = false;
	if (std::abs(x0 - x1)<std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0>x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	for (int x = x0; x <= x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0*(1. - t) + y1*t;
		if (steep) {
			image.setPixel(y, x, color);
		}
		else {
			image.setPixel(x, y, color);
		}
	}
}

void triangle(Vec3i t0, Vec3i t1, Vec3i t2, sf::Image &image, sf::Color color, std::vector<int>& zbuffer) {
	if (t0.y == t1.y && t0.y == t2.y) return; // i dont care about degenerate triangles
	if (t0.y>t1.y) std::swap(t0, t1);
	if (t0.y>t2.y) std::swap(t0, t2);
	if (t1.y>t2.y) std::swap(t1, t2);
	int total_height = t2.y - t0.y;
	for (int i = 0; i<total_height; i++) {
		bool second_half = i>t1.y - t0.y || t1.y == t0.y;
		int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
		float alpha = (float)i / total_height;
		float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height; // be careful: with above conditions no division by zero here
		Vec3i A = ToVec3i(Vec3f(t0) + Vec3f(t2 - t0)*alpha);
		Vec3i B = ToVec3i(second_half ? Vec3f(t1) + Vec3f(t2 - t1)*beta : Vec3f(t0) + Vec3f(t1 - t0)*beta);
		if (A.x>B.x) std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) {
			float phi = B.x == A.x ? 1. : (float)(j - A.x) / (float)(B.x - A.x);
			Vec3i P = ToVec3i(Vec3f(A) + Vec3f(B - A)*phi);
			int idx = P.x + P.y*width;
			if (zbuffer[idx]<P.z) {
				zbuffer[idx] = P.z;
				image.setPixel(P.x, P.y, color);
			}
		}
	}
}/**/

void wireRender(Model *mod, sf::Image &sfimage) {//проволочная модель
	float zoom = 200;
	for (int i = 0; i < mod->nfaces(); i++) { 
		//TGAColor randColor = TGAColor(rand() % 205 + 50, rand() % 205 + 50, rand() % 205 + 50, 255);
		int *face = mod->faces[i].f;

		for (int j = 0; j < 3; j++) {
			Vec3f v0 = mod->vert(face[j]); // массив face содержит индексы трёх вершин, которые надо соединить vert получает вершину по её индексу
			Vec3f v1 = mod->vert(face[(j + 1) % 3]);

			/*int x0t = zoom * (v0.x / v0.z) + width / 2; not work
			int y0t = zoom * (v0.y / v0.z) + height / 2;
			int x1t = zoom * (v1.x / v1.z) + width / 2;
			int y1t = zoom * (v1.y / v1.z) + height / 2;*/

			int x0 = (v0.x + 1.)*width / 2.;
			int y0 = (v0.y + 1.)*height / 2.;
			int x1 = (v1.x + 1.)*width / 2.;
			int y1 = (v1.y + 1.)*height / 2.;

			//line(x0, y0, x1, y1, image, white);
			line(x0, y0, x1, y1, sfimage, sf::Color::White);
		}/**/
	}
}

void triangleRender(Model *mod, sf::Image &sfimage) { //треугольный рендер
	std::vector<int> zbuffer(height*width);
	Vec3f light_dir(0, 0, -1);
	for (int i = 0; i<mod->nfaces(); i++) {
		int *face = mod->faces[i].f;
		Vec3f v0 = mod->vert(face[0]);
		Vec3f v1 = mod->vert(face[1]);
		Vec3f v2 = mod->vert(face[2]);
		Vec3f world_coords[] = { v0, v1, v2 };

		Vec3i screen_coords[3];
		screen_coords[0] = Vec3i((v0.x + 1.) * width / 2., (v0.y + 1.)*height / 2., (v0.z + 1.)*depth / 2.);
		screen_coords[1] = Vec3i((v1.x + 1.) * width / 2., (v1.y + 1.)*height / 2., (v1.z + 1.)*depth / 2.);
		screen_coords[2] = Vec3i((v2.x + 1.) * width / 2., (v2.y + 1.)*height / 2., (v2.z + 1.)*depth / 2.);

		//--------------------------------------------------------------------------------------------------- свет?

		Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]); // находим нормаль к тругольнику как векторное ^ произведение двух векторов этого треугольника
		n.norm();
		float intensity = n*light_dir; //скалярное произведение
		if (intensity>0) {
			triangle(screen_coords[0], screen_coords[1], screen_coords[2], sfimage, sf::Color(intensity * 255, intensity * 255, intensity * 255, 255), zbuffer);
		}
	}
}

int main()
{

	std::cout << "WASD - Control, 1 - 2 mode\n";
	sf::RenderWindow window(sf::VideoMode(width, height), "Cubik"); //создаем окно

	std::string cube = "models/cube.obj";
	std::string negr = "models/african_head.obj";

	//Model *mod = new Model(negr);
	Model *mod = new Model(cube);

	sf::Image sfimage;
	sfimage.create(width, height);
	wireRender(mod, sfimage);

	int mode = 0;
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				sfimage.create(width, height);
				if (event.key.code == sf::Keyboard::A)
					mod->rotateY(1);
				if (event.key.code == sf::Keyboard::D)
					mod->rotateY(-1);
				if (event.key.code == sf::Keyboard::W)
					mod->rotateX(-1);
				if (event.key.code == sf::Keyboard::S)
					mod->rotateX(1);
				if (event.key.code == sf::Keyboard::Num1)
					mode = 0;
				if (event.key.code == sf::Keyboard::Num2)
					mode = 1;

				if (mode == 0)
					wireRender(mod, sfimage);
				else if (mode == 1)
					triangleRender(mod, sfimage);
			}
		}		

		sf::Texture texture; //что бы отобразить картинку в окне надо превратить её в спрайт, для этого надо превратить её в текстуру
		texture.loadFromImage(sfimage);
		sf::Sprite sprite;
		sprite.setTexture(texture, true);

		window.clear(); //очистить окно
		window.draw(sprite); //нарисовать
		window.display(); //отобразить

		//Sleep(10);

	}

	delete mod;
	return 0;
}