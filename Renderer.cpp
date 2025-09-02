#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "Renderer.h"
#include "Light.h"
#include "PointLight.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

float yScroll;
float mouseX;
float mouseY;

glm::mat4 Renderer::ID = glm::mat4(1.0f);

void getColor(float count, float vertices[], int len) {
	
	float red;
	float green;
	float blue;
	if (count >= 0 && count < 255) {
		red = 1.0;
		green = count / 255;
		blue = 0;
	}
	else if (count >= 255 && count < 510) {
		red = (-count + 510) / 255;
		green = 1.0;
		blue = 0;
	}
	else if (count >= 510 && count < 765) {
		red = 0.0;
		green = 1.0;
		blue = (count - 510) / 255;
	}
	else if (count >= 765 && count < 1020) {
		red = 0.0;
		green = (-count + 1020) / 255;
		blue = 1.0;
	}
	else if (count >= 1020 && count < 1275) {
		red = (count - 1020) / 255;
		green = 0.0;
		blue = 1.0;
	}
	else {
		red = 1.0;
		green = 0.0;
		blue = (-count + 1530) / 255;
	}

	for (int i = 0; i < len / 8; i++) {
		int index = i * 8;
		vertices[index + 3] = red;
		vertices[index + 4] = green;
		vertices[index + 5] = blue;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xOff, double yOff) {
	yScroll = yOff;
}

void cursor_position_callback(GLFWwindow* window, double xPos, double yPos) {
	mouseX = xPos;
	mouseY = yPos;
}

void processInput(GLFWwindow* window) {

	int x = 0;
	int y = 0;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		glfwSetWindowOpacity(window, 0.5);
		glfwSetWindowTitle(window, "Spooky Ghost Window");
	}
	else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		glfwSetWindowOpacity(window, 1.0);
		glfwSetWindowTitle(window, "Last Time");
	}
	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		glfwSetWindowOpacity(window, 0.0);
		glfwSetWindowTitle(window, "You Cannot See This Text");
	}
	else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glfwSetWindowTitle(window, "Wireframe");
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		glfwGetWindowPos(window, &x, &y);
		glfwSetWindowPos(window, 0, y - 1);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		glfwGetWindowPos(window, &x, &y);
		glfwSetWindowPos(window, 0, y + 1);
	}
	else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glfwSetWindowTitle(window, "Last Time");
	}

}

GLFWwindow* Renderer::init() {

	stbi_set_flip_vertically_on_load(true);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "Last Time", NULL, NULL);

	if (window == NULL) {
		std::cout << "ERROR: GLFW window creation failed\n";
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
		std::cout << "ERROR: Failed to initialize GLAD\n";
		return NULL;
	}

	glViewport(0, 0, 800, 800); 

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetScrollCallback(window, scroll_callback);

	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glGenBuffers(1, Light::getLightUBO());
	glBindBuffer(GL_UNIFORM_BUFFER, *Light::getLightUBO());
	glBufferData(GL_UNIFORM_BUFFER, 48 * 32, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, *Light::getLightUBO());

	return window;
}

int Renderer::render(GLFWwindow* window)
{

	Shader objectShader("vertex.glsl", "objectFragment.glsl");
	Shader lightShader("vertex.glsl", "lightFragment.glsl");

	objectShader.use();
	glUniform1i(glGetUniformLocation(objectShader.getShaderID(), "texture1"), 0);
	lightShader.use();
	glUniform1i(glGetUniformLocation(lightShader.getShaderID(), "texture1"), 0);

	glUniformBlockBinding(objectShader.getShaderID(), glGetUniformBlockIndex(objectShader.getShaderID(), "Lights"), 0);

	glm::mat4 ID = glm::mat4(1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = ID;

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10000.0f);


	float lastTime = 0.0f;
	float tDiff = 0.0f;

	int windowWidth = 0;
	int windowHeight = 0;

	float cameraX = 0;
	float cameraY = 0;
	float cameraZ = 0;
	float cameraSpeed = 3.0f;
	float FOV = 45.0f;

	float cameraThetaY = 0;
	float cameraThetaX = 0;

	bool cursorLock = true;
	bool esc = false;

	int UBOSize = 0;


	yScroll = 0.0f;

	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	float horizontalAspect = windowWidth / windowHeight;

	float diagonalAspect = sqrt(horizontalAspect * horizontalAspect + 1);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
	
	while (!glfwWindowShouldClose(window))
	{

		//std::cout << (*Light::getLights(0)).getColor().z << "\n";

		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		tDiff = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		

		std::cout << "FPS: " << 1 / tDiff << "\n";
		

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraZ += cameraSpeed * cos(cameraThetaY) * tDiff * cos(-cameraThetaX);
			cameraX += cameraSpeed * cos(cameraThetaY) * tDiff * sin(-cameraThetaX);
			cameraY += cameraSpeed * tDiff * sin(cameraThetaY);
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraZ -= cameraSpeed * cos(cameraThetaY) * tDiff * cos(-cameraThetaX);
			cameraX -= cameraSpeed * cos(cameraThetaY) * tDiff * sin(-cameraThetaX);
			cameraY -= cameraSpeed * tDiff * sin(cameraThetaY);
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraZ += cameraSpeed * tDiff * sin(cameraThetaX);
			cameraX += cameraSpeed * tDiff * cos(cameraThetaX);
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraZ -= cameraSpeed * tDiff * sin(cameraThetaX);
			cameraX -= cameraSpeed * tDiff * cos(cameraThetaX);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && esc) {
			cursorLock = !cursorLock;
			esc = false;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && !esc) {
			esc = true;
		}

		cameraSpeed += yScroll;

		if (cursorLock) {
			cameraThetaX += 0.5 * (mouseX - (windowWidth / 2)) * tDiff;
			cameraThetaY += 0.5 * (mouseY - (windowHeight / 2)) * tDiff;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}


		if (yScroll != 0) {
			yScroll = 0.0f;
		}


		projection = glm::perspective(glm::radians(45.0f), ((float)windowWidth) / windowHeight, 0.01f, 500.0f);

		objectShader.use();
		glUniformMatrix4fv(glGetUniformLocation(objectShader.getShaderID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		lightShader.use();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.getShaderID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_DEPTH_BUFFER_BIT);
		

		

		if (cursorLock) {

			glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		}

		

		//(*Light::getLights(0)).setPos(glm::vec3(9 * cos(lastTime * 2) + 5, 3 * sin(lastTime * 4) + 4, 9 * sin(lastTime * 2) + 5)); // Change light position
		
		//color = glm::vec3(fmax(fmin(abs((fmod(lastTime, 6)) - 3) - 1, 1.0f), 0.0f), fmax(fmin(-abs(fmod(lastTime, 6) - 2) + 2, 1.0f), 0.0f), fmax(fmin(-abs(fmod(lastTime, 6) - 4) + 2, 1.0f), 0.0f));
		//(*Light::getLights(0)).setColor(color); // Change light color

		//std::cout << sizeof(float) << " + 2 * " << sizeof(glm::vec3) << " = " << sizeof(PointLightStruct) << "\n";
		
		for (int i = 0; i < Object::getObjects().size(); i++) {

			glBindBuffer(GL_ARRAY_BUFFER, (*Object::getObjects(i)).getVBO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*Object::getObjects(i)).getEBO());
			glBindVertexArray((*Object::getObjects(i)).getVAO());
			glBufferData(GL_ARRAY_BUFFER, (*Object::getObjects(i)).getVertices().size() * sizeof(float), &Object::getObjects().at(i).getVertices()[0], GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*Object::getObjects(i)).getIndices().size() * sizeof(unsigned int), &Object::getObjects().at(i).getIndices()[0], GL_STATIC_DRAW);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, (*Object::getObjects(i)).getTexture());


			model = (*Object::getObjects(i)).updateModel();

			
			view = glm::rotate(ID, cameraThetaX, glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::rotate(view, cameraThetaY, glm::vec3(cos(cameraThetaX), 0.0f, sin(cameraThetaX)));
			view = glm::translate(view, glm::vec3(cameraX, cameraY, cameraZ));
			
			if (!(*Object::getObjects(i)).getIsLight()) {
				objectShader.use();
				objectShader.setMat4("model", model);
				objectShader.setMat4("view", view);
				//objectShader.setVec3("lightColor", (*Light::getLights(0)).getColor());
				//std::cout << (*Light::getLights(0)).getColor().x << "\n";
				objectShader.setInt("numLights", PointLight::getPointLights().size());
				objectShader.setVec3("camera.pos", glm::vec3(-cameraX, -cameraY, -cameraZ));
				objectShader.setFloat("specularStrength", (*Object::getObjects(i)).getSpecularStrength());
				objectShader.setFloat("specularExp", (*Object::getObjects(i)).getSpecularExp());
				glBindBuffer(GL_UNIFORM_BUFFER, *Light::getLightUBO());
				glBufferSubData(GL_UNIFORM_BUFFER, 0, 32 * PointLight::getPointLightStructs().size(), &(PointLight::getPointLightStructs().at(0)));
			}
			else {
				lightShader.use();
				lightShader.setMat4("model", model);
				lightShader.setMat4("view", view);
				lightShader.setVec3("lightColor", (*Light::getLights(0)).getColor()); // 
				//std::cout << (*Light::getLights(0)).getColor().x << "\n";
			}

			

			//objectShader.setVec3("lightPos", (*Light::getLights(0)).getPos());
			//objectShader.setFloat("lightRadius", (*Light::getLights(0)).getRadius());
			



			glDrawElements(GL_TRIANGLES, (*Object::getObjects(i)).getIndices().size(), GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}