#include "Plane.h"

Plane::Plane(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, unsigned int tex, float specStr, float specExp) : Object({0.0f}, { 0 }, pos, rot, scale, tex, specStr, specExp) {
	// Position (3) Color (3) Texture (2)
	std::vector<float> planeVertices = {
		-0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 0 pos pos pos color color color texCoord texCoord normal normal normal
		-0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, // 1
		 0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 2
		 0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f  // 3
	};


	std::vector<unsigned int> indices = {
		1, 2, 0,
		3, 2, 1
	};

	//std::cout << planeVertices[1] << "\n";

	Object::vertices = planeVertices;
	Object::indices = indices;

	//std::cout << Plane::vertices[1] << "\n";
	//std::cout << Object::getVertices().size() << "\n";

	//std::cout << this->getObjType() << "\n";

	Object::addObject(this);

	glBufferData(GL_ARRAY_BUFFER, Object::vertices.size() * sizeof(float), &Object::vertices[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, (*Object::getObjects(i)).getVertices().size() * sizeof(float), &(*Object::getObjects().at(i)).getVertices()[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Object::indices.size() * sizeof(unsigned int), &Object::indices[0], GL_STATIC_DRAW);
	
}

objType Plane::getObjType() {
	return PLANE;
}