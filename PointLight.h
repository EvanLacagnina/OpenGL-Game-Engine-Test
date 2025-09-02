#pragma once
#include "Light.h"

struct PointLightStruct {
	glm::vec3 pos;
	float pad;
	glm::vec3 color;
	float radius;
};

class PointLight : Light {

protected:
	static std::vector<PointLight> pointLights; 

	static std::vector<PointLightStruct> pointLightStructs;
public:
	PointLight(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, glm::vec3 color, float radius);

	static std::vector<PointLight> getPointLights();
	static PointLight* getPointLights(int i);

	static void addPointLight(PointLight pointLight);

	static std::vector<PointLightStruct> getPointLightStructs();
};