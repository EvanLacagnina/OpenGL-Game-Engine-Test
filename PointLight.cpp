#include "PointLight.h"

//std::vector<float> PointLight::lightRadii;
std::vector<PointLight> PointLight::pointLights;
std::vector<PointLightStruct> PointLight::pointLightStructs;

PointLight::PointLight(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, glm::vec3 color, float radius) : Light(vertices, indices, pos, rot, scale, tex, color) {
	PointLight::pointLights.push_back(*this);
	PointLight::pointLightStructs.push_back({ pos, 1.0f, color, radius,});
}

std::vector<PointLight> PointLight::getPointLights() {
	return PointLight::pointLights;
}

PointLight* PointLight::getPointLights(int i) {
	return &(PointLight::pointLights[i]);
}

void PointLight::addPointLight(PointLight pointLight) {
	PointLight::pointLights.push_back(pointLight);
}

std::vector<PointLightStruct> PointLight::getPointLightStructs() {
	return PointLight::pointLightStructs;
}

objType PointLight::getObjType() {
	//std::cout << "M";
	return POINTLIGHT;
}