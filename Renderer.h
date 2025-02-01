#pragma once
#include <vector>
#include "Object.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
	static glm::mat4 ID;

	static GLFWwindow* init();
	static int render(GLFWwindow* window, std::vector<Object> objects);
};