#include "main.h"

	std::vector<DirectionalLight*> DirectionalLight::dirLights;

	std::vector<DirectionalLightStruct*> DirectionalLight::dirLightStructs;

	DirectionalLight::DirectionalLight(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 size, unsigned int tex, glm::vec3 color, float brightness) : Light(vertices, indices, pos, rot, scale, tex, color) {
		DirectionalLight::dirLights.push_back(this);
		
		DirectionalLight::dirLightStruct = *new DirectionalLightStruct{ pos, brightness, rot, 0.0f, color, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, size, 0.0f, Renderer::ID};
		DirectionalLight::dirLightStructs.push_back(&(DirectionalLight::dirLightStruct));
		//DirectionalLight::dirLightStruct = *DirectionalLight::dirLightStructs.at(DirectionalLight::dirLightStructs.size() - 1);
	}

	std::vector<DirectionalLight*> DirectionalLight::getDirLights() {
		return dirLights;
	}
	DirectionalLight* DirectionalLight::getDirLights(int i) {
		return dirLights.at(i);
	}

	void DirectionalLight::addDirLight(DirectionalLight dirLight) {
		dirLights.push_back(&dirLight);
	}

	std::vector<DirectionalLightStruct*> DirectionalLight::getDirLightStructs() {
		return dirLightStructs;
	}

	void DirectionalLight::updateDirLights() {
		glm::mat4 rotMat = Renderer::ID;
		for (DirectionalLight* light : dirLights) {
			rotMat = glm::rotate(Renderer::ID, glm::radians((*light).getRot()[0]), glm::vec3(1.0f, 0.0f, 0.0f));
			rotMat = glm::rotate(rotMat, glm::radians((*light).getRot()[1]), glm::vec3(0.0f, cos(glm::radians((*light).rot[0])), sin(glm::radians((*light).rot[0]))));
			rotMat = glm::rotate(rotMat, glm::radians((*light).getRot()[2]), glm::vec3(cos(glm::radians((*light).rot[0])) * sin(glm::radians((*light).rot[1])), sin(glm::radians((*light).rot[0])), cos(glm::radians((*light).rot[0])) * cos(glm::radians((*light).rot[1]))));
			(*light).getDirLightStruct()->invRot = glm::inverse(rotMat);
			(*light).getDirLightStruct()->dir = rotMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
			//std::cout << (*light).getDirLightStruct()->dir.z << "\n";
		}
	}

	DirectionalLightStruct* DirectionalLight::getDirLightStruct() {
		return &dirLightStruct;
	}

	objType DirectionalLight::getObjType() {
		return DIRLIGHT;
	}