#include "DirectionalLight.h"

	std::vector<DirectionalLight> DirectionalLight::dirLights;

	std::vector<DirectionalLightStruct> DirectionalLight::dirLightStructs;

	DirectionalLight::DirectionalLight(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 size, unsigned int tex, glm::vec3 color) : Light(vertices, indices, pos, rot, scale, tex, color) {
		DirectionalLight::dirLights.push_back(*this);
		DirectionalLight::dirLightStructs.push_back({pos, 0.0f, rot, 0.0f, color, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f) * rot, 0.0f, size, 0.0f});

	}

	std::vector<DirectionalLight> DirectionalLight::getDirLights() {
		return dirLights;
	}
	DirectionalLight DirectionalLight::getDirLights(int i) {
		return dirLights.at(i);
	}

	void DirectionalLight::addDirLight(DirectionalLight dirLight) {
		dirLights.push_back(dirLight);
	}

	std::vector<DirectionalLightStruct> DirectionalLight::getDirLightStructs() {
		return dirLightStructs;
	}