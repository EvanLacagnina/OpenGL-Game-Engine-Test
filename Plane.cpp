#include "Plane.h"

Plane::Plane(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex) : Object({0.0f}, pos, rot, scale, tex, 48) {
	// Position (3) Color (3) Texture (2)
	std::vector<float> planeVertices = {
		-0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 0.0f,
		-0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 5.0f,
		-0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 5.0f,
		 0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 0.0f,
		 0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 5.0f
	};

	//std::cout << planeVertices[1] << "\n";

	Object::vertices = planeVertices;

	//std::cout << Plane::vertices[1] << "\n";
	//std::cout << Object::getVertices().size() << "\n";
}