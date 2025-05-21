#pragma once
#include "Object.h"

class Light : Object {
private:
protected:
	glm::vec3 color;

	static std::vector<Light> lights;
public:
	Light(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, int numVertices, glm::vec3 color);

	glm::vec3 getColor();

	static Light getLights(int i);

	static void addLight(Light light);
};