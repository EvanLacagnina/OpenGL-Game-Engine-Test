#include "Light.h"

std::vector<Light> Light::lights;
std::vector<glm::vec3> Light::lightPos;
std::vector<glm::vec3> Light::lightColors;
unsigned int Light::lightUBO;

Light::Light(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, glm::vec3 color) : Object(vertices, indices, pos, rot, scale, tex, 0.0f, 0.0f) {
	Object::isLight = true;
	Light::color = color;


	Object::addObject(*this);
	Light::addLight(*this);
	Light::lightPos.push_back(pos);
	Light::lightColors.push_back(color);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

glm::vec3 Light::getColor() {
	return Light::color;
}

glm::vec3 Light::getPos() {
	//std::cout << "Light getPos: " << Object::getPos().x << "\n";
	return Object::getPos();
}

std::vector<Light> Light::getLights() {
	return Light::lights;
}

Light* Light::getLights(int i) {
	return &Light::lights.at(i);
}

std::vector<glm::vec3> Light::getLightPos() {
	return Light::lightPos;
}

std::vector<glm::vec3> Light::getLightColors() {
	return Light::lightColors;
}

void Light::addLight(Light light) {
	Light::lights.push_back(light);
}

void Light::setPos (glm::vec3 pos) {
	Object::setPos(pos);
	(*Object::getObjects(index)).setPos(pos);
}

void Light::setColor(glm::vec3 color) {
	this->color = color;
	(*Object::getObjects(index)).setColor(color);
}

unsigned int* Light::getLightUBO() {
	return &Light::lightUBO;
}