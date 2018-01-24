#include "model.h"

std::vector<std::string> splitString(std::string str, char c)
{
	std::vector<std::string> elems;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, c)) {
		elems.push_back(item);
	}
	return elems;
}

Model::Model(std::string filename) { //pre-initialization
	std::ifstream input(filename);

	std::string line;
	while (std::getline(input, line))
	{
		if (line.size() == 0 || line[0] == '#')
			continue;

		std::istringstream ss(line);
		std::string com;
		ss >> com;

		if (com == "v"){
			std::vector<std::string> args = splitString(line, ' ');
			//verts.push_back(Vec3f(std::stof(args[1]), std::stof(args[2]), std::stof(args[3])));
			verts.push_back(Vec3f(std::stof(args[1]), std::stof(args[2]), std::stof(args[3])));
			//verts_.push_back(Vec3float(std::stof(args[1]), std::stof(args[2]), std::stof(args[3])));
		}

		if (com == "vn"){
			std::vector<std::string> args = splitString(line, ' ');
			norms.push_back(Vec3f(std::stof(args[1]), std::stof(args[2]), std::stof(args[3])));
		}
		else
			if (com == "f")	{
				std::vector<std::string> args = splitString(line, ' ');
				for (unsigned int i = 0; i<args.size() - 3; i++){
					Face face;
					face.f[0] = std::stoi(splitString(args[1], '/')[0]) - 1;
					face.f[1] = std::stoi(splitString(args[2 + i], '/')[0]) - 1;
					face.f[2] = std::stoi(splitString(args[3 + i], '/')[0]) - 1;

					face.n[0] = std::stoi(splitString(args[1], '/')[2]) - 1;
					face.n[1] = std::stoi(splitString(args[2 + i], '/')[2]) - 1;
					face.n[2] = std::stoi(splitString(args[3 + i], '/')[2]) - 1;
					faces.push_back(face);
				}

			}
	}
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts.size();
}

int Model::nfaces() {
    return (int)faces.size();
}

Vec3f Model::vert(int i) {
    return verts[i];
}

void Model::rotateX(float degree)
{
	float rad = degree * 3.14159269795358325 / 180;
	float y, z;
	for (int i = 0; i < nverts(); i++) {	
		y = cos(rad)*verts[i].y + sin(rad)*verts[i].z;
		z = -1 * sin(rad)*verts[i].y + cos(rad)*verts[i].z;
		verts[i].y = y;
		verts[i].z = z;
	}
}

void Model::rotateY(float degree)
{
	float rad = degree * 3.14159269795358325 / 180;
	float x, z;
	for (int i = 0; i < nverts(); i++) {		
		x = cos(rad)*verts[i].x + -1 * sin(rad)*verts[i].z;
		z = sin(rad)*verts[i].x + cos(rad)*verts[i].z;
		verts[i].x = x;
		verts[i].z = z;
	}
}

