#include "Light.h"

std::vector<Light> Light::lights;

Light::Light(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, int numVertices, glm::vec3 color) : Object(vertices, indices, pos, rot, scale, tex, numVertices) {
	Object::isLight = true;
	Light::color = color;


	Object::addObject(*this);
	Light::addLight(*this);
}

glm::vec3 Light::getColor() {
	return Light::color;
}

Light Light::getLights(int i) {
	return Light::lights.at(i);
}

void Light::addLight(Light light) {
	Light::lights.push_back(light);
}