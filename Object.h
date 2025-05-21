#pragma once
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <glad/glad.h>
#include <vector>
//#include "Object.h"
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
	std::vector<unsigned int> indices;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	static std::vector<Object> objects, lights;

	int index;

	bool isLight;

public:
	Object(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, int numVertices);

	unsigned int getTexture();

	glm::mat4 updateModel(glm::vec3 cameraPos);

	void setPos(glm::vec3 pos);
	void setRot(glm::vec3 rot);
	void setScale(glm::vec3 scale);

	static void addObject(Object obj);

	glm::vec3 getPos();
	glm::vec3 getRot();
	glm::vec3 getScale();

	bool getIsLight();

	static std::vector<Object> getObjects();
	static Object getObjects(int i);

	int getNumVertices();
	std::vector<float> getVertices();
	std::vector<unsigned int> getIndices();
	float getVertex(int i);
	unsigned int getVBO();
	unsigned int getVAO();
	unsigned int getEBO();
};