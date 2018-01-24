#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "MyMath.h"


class Model {
	struct Face {
		int f[3];  //грани
		int n[3]; //нормали
	};

private:	
	std::vector<Vec3f> norms;

public:
	Model(std::string filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<Vec3f> verts;
	std::vector<Face> faces;
	void rotateX(float degree);
	void rotateY(float degree);
	
};
