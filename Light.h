#pragma once
#include "Object.h"

class Light : Object {
private:
protected:
	glm::vec3 color;

	float radius;

	static std::vector<Light> lights;
	static std::vector<glm::vec3> lightPos;
	static std::vector<glm::vec3> lightColors;
	static std::vector<float> lightRadii;
public:
	Light(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, int numVertices, glm::vec3 color, float radius);

	glm::vec3 getColor();
	glm::vec3 getPos();
	float getRadius();

	static std::vector<Light> getLights();
	static Light* getLights(int i);
	static std::vector<glm::vec3> getLightPos();
	static std::vector<glm::vec3> getLightColors();
	static std::vector<float> getLightRadii();

	static void addLight(Light light);

	void setPos(glm::vec3 pos);

	void setColor(glm::vec3 color);
};