#pragma once
#include "Object.h"

class Plane : public Object {
private:
	std::vector<float> vertices;

public:
	Plane(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, float specStr, float specExp);

	objType getObjType() override;
};