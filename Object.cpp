#include "Object.h"
#include "Renderer.h"

std::vector<Object> Object::objects, Object::lights;

Object::Object(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, int numVertices) {
	Object::vertices = vertices;
	Object::indices = indices;
	Object::pos = pos;
	Object::rot = rot;
	Object::scale = scale;
	Object::texture = tex;
	Object::numVertices = numVertices;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBufferData(GL_ARRAY_BUFFER, Object::vertices.size() * sizeof(float), &Object::vertices[0], GL_STATIC_DRAW);
	
	index = objects.size();
}

unsigned int Object::getTexture() {
	return Object::texture;
}

glm::mat4 Object::updateModel(glm::vec3 cameraPos) {
	
	Object::model = glm::translate(Renderer::ID, -Object::pos + cameraPos);
	//std::cout << "(" << Object::pos[0] << ", " << Object::pos[1] << ", " << Object::pos[2] << ")\n";

	//Object::rot %= glm::vec3(6.283185307179586476925286766559, 6.283185307179586476925286766559, 6.283185307179586476925286766559);
	Object::model = glm::rotate(Object::model, glm::radians(Object::rot[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	Object::model = glm::rotate(Object::model, glm::radians(Object::rot[1]), glm::vec3(0.0f, cos(glm::radians(Object::rot[0])), sin(glm::radians(Object::rot[0]))));
	Object::model = glm::rotate(Object::model, glm::radians(Object::rot[2]), glm::vec3(cos(glm::radians(Object::rot[0])) * sin(glm::radians(Object::rot[1])), sin(glm::radians(Object::rot[0])), cos(glm::radians(Object::rot[0])) * cos(glm::radians(Object::rot[1]))));
	//std::cout << "(" << 

	Object::model = glm::scale(Object::model, Object::scale);

	return Object::model;
}

void Object::setPos(glm::vec3 pos) {
	Object::pos = pos;
}

void Object::setRot(glm::vec3 rot) {
	Object::rot = rot;
}

void Object::setScale(glm::vec3 scale) {
	Object::scale = scale;
}

void Object::addObject(Object obj) {
	objects.push_back(obj);
}

glm::vec3 Object::getPos() {
	return Object::pos;
}
glm::vec3 Object::getRot() {
	return Object::rot;
}
glm::vec3 Object::getScale() {
	return Object::scale;
}

std::vector<Object> Object::getObjects() {
	return objects;
}

Object Object::getObjects(int i) {
	return objects.at(i);
}

int Object::getNumVertices() {
	return numVertices;
}

std::vector<float> Object::getVertices() {
	return Object::vertices;
}

std::vector<unsigned int> Object::getIndices() {
	return Object::indices;
}

float Object::getVertex(int i) {
	return Object::vertices[i];
}

unsigned int Object::getVBO() {
	return Object::VBO;
}

unsigned int Object::getVAO() {
	return Object::VAO;
}

unsigned int Object::getEBO() {
	return Object::EBO;
}