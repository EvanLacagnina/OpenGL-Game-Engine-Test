#pragma once
#include "Object.h"

class Cube : public Object {
private:
	std::vector<float> vertices;

public:
	Cube(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex);
};