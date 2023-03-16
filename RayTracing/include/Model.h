#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Triangle.h"

struct Face
{
	int vertex_ins[3];
	int texture_ins[3];
	int normal;
};

class Model {
public:
	Model();
	~Model();

	int LoadFromOBJ(const char* filename);

	int m_triangleCount = 0;
	std::vector<glm::vec3*> m_verticies;
	std::vector<glm::vec3*> m_normals;
	std::vector<Face*> m_faces;
	std::vector<Triangle*> m_triangles;
	glm::vec3 Position{ 0.0f };

	void PrintAll();

private:
	void MakeTriangles();
	void CleanTrash();
};