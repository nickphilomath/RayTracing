#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Model.h"

struct Sphere
{
	glm::vec3 Position{0.0f};
	float Radius = 0.5f;
	glm::vec3 Albedo{1.0f};
};

struct Scene
{
	std::vector<Sphere> Spheres;
	std::vector<Triangle> Triangles;
	std::vector<Model*> Models;
};