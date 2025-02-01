#include "Object.h"
#include "Renderer.h"

Object::Object(std::vector<float> vertices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, int numVertices) {
	Object::vertices = vertices;
	Object::pos = pos;
	Object::rot = rot;
	Object::scale = scale;
	Object::texture = tex;
	Object::numVertices = numVertices;
	glGenBuffers(1, &VBO);
	glBufferData(VBO, Object::vertices.size() * sizeof(float), &Object::vertices[0], GL_STATIC_DRAW);
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

glm::vec3 Object::getPos() {
	return Object::pos;
}
glm::vec3 Object::getRot() {
	return Object::rot;
}
glm::vec3 Object::getScale() {
	return Object::scale;
}

int Object::getNumVertices() {
	return numVertices;
}

std::vector<float> Object::getVertices() {
	return Object::vertices;
}

float Object::getVertex(int i) {
	return Object::vertices[i];
}

unsigned int Object::getVBO() {
	return Object::VBO;
}