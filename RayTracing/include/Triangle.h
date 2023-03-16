#pragma once

#include <glm/glm.hpp>

struct Triangle {
	glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 Albedo{ 1.0f };
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 C;
	glm::vec3 Normal;
};