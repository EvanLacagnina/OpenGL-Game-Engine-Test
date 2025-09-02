#pragma once
#include "Object.h"

class Light : Object {
private:
protected:
	glm::vec3 color;

	static unsigned int lightUBO;

	static std::vector<Light> lights;
	static std::vector<glm::vec3> lightPos;
	static std::vector<glm::vec3> lightColors;
public:
	Light(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, glm::vec3 color);

	glm::vec3 getColor();
	glm::vec3 getPos();

	static std::vector<Light> getLights();
	static Light* getLights(int i);

	static void addLight(Light light);

	static std::vector<glm::vec3> getLightPos();
	static std::vector<glm::vec3> getLightColors();

	void setPos(glm::vec3 pos);

	void setColor(glm::vec3 color);

	static unsigned int* getLightUBO();
};