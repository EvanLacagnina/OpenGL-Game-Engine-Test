#pragma once
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <glad/glad.h>
#include <vector>
//#include <GLFW/glfw3.h>

class Object 
{
private:
	
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;

	glm::mat4 model;

	unsigned int texture;

	int numVertices;

protected:
	std::vector<float> vertices;
	unsigned int VBO;

public:
	Object(std::vector<float> vertices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, int numVertices);

	unsigned int getTexture();

	glm::mat4 updateModel(glm::vec3 cameraPos);

	void setPos(glm::vec3 pos);
	void setRot(glm::vec3 rot);
	void setScale(glm::vec3 scale);

	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScale();

	int getNumVertices();
	std::vector<float> getVertices();
	float getVertex(int i);
	unsigned int getVBO();
};