#pragma once
#include "Light.h"

struct DirectionalLightStruct {
	glm::vec3 pos;
	float brightness;
	glm::vec3 rot;
	float pad1;
	glm::vec3 color;
	float pad2;
	glm::vec3 dir;
	float pad3;
	glm::vec3 size;
	float pad4;
	glm::mat4 invRot; // 16N
};

class DirectionalLight : public Light {
protected:
	static std::vector<DirectionalLight*> dirLights;

	static std::vector<DirectionalLightStruct*> dirLightStructs;

	DirectionalLightStruct dirLightStruct;
public:
	DirectionalLight(std::vector<float> vertices, std::vector<unsigned int> indices, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 size, unsigned int tex, glm::vec3 color, float brightness);

	static std::vector<DirectionalLight*> getDirLights();
	static DirectionalLight* getDirLights(int i);

	static void addDirLight(DirectionalLight dirLight);

	static std::vector<DirectionalLightStruct*> getDirLightStructs();

	static void updateDirLights();

	DirectionalLightStruct* getDirLightStruct();

	objType getObjType() override;
};